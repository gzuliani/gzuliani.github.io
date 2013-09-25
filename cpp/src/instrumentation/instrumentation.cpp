#include "instrumentation.h"

#include <iomanip>
#include <map>

#define NOMINMAX
#define WIN32_EXTRA_LEAN
#include <windows.h>

using namespace Instrumentation;

// compile target with /Gh /GH options
// link target against this library
// use a map file (/MAP linker flag) to resolve addresses

// ############################################################################
//	CLASS Hook

Hook::Observer::~Observer()
{

} // Hook::Observer::~Observer

Hook::Hook(Observer* observer)
	:	m_observer(observer)
{
	m_enabled = true;

} // Hook::Hook

Hook::~Hook()
{
	m_enabled = false;
	delete m_observer;

} // Hook::~Hook

void _stdcall Hook::EnterFn(unsigned frame)
{
	if (!m_instance->m_enabled)
		return;

	m_instance->m_enabled = false;
	m_instance->m_observer->Start(frame);
	m_instance->m_enabled = true;

} // Hook::EnterFn

void _stdcall Hook::ExitFn(unsigned frame)
{
	if (!m_instance->m_enabled)
		return;

	m_instance->m_enabled = false;
	m_instance->m_observer->End(frame);
	m_instance->m_enabled = true;

} // Hook::ExitFn

// ############################################################################
//	CLASS FnCall

FnCall::FnCall(size_t id, size_t parentId, unsigned frame, double start)
	:	m_id(id),
		m_parentId(parentId),
		m_frame(frame),
		m_address(*((unsigned*)frame) - 5),
		m_start(start),
		m_end(0)
{

} // FnCall::FnCall

void FnCall::End(double end)
{
	m_end = end;

} // FnCall::End

bool FnCall::Completed() const
{
	return m_end != 0;

} // FnCall::Completed

double FnCall::Duration() const
{
	return m_end - m_start;

} // FnCall::Duration

// ############################################################################
//	CLASS Tracer

Tracer::Logger::~Logger()
{

} // Tracer::Logger::~Logger

Tracer::Tracer(Logger* logger)
	:	m_logger (logger)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	m_frequency = static_cast<double>(frequency.QuadPart);

} // Tracer::Tracer

Tracer::~Tracer()
{
	if (!m_fnStack.empty())
		; // !!!

	std::vector<FnCall>::const_iterator fnCall = m_fnCalls.begin();

	for (; fnCall != m_fnCalls.end(); ++fnCall)
		m_logger->Log(*fnCall);

	delete m_logger;

} // Tracer::~Tracer

void Tracer::Start(unsigned frame)
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	m_fnCalls.push_back(
		FnCall(
			m_fnCalls.size(),
			m_fnStack.empty() ? -1 : m_fnStack.top(),
			frame,
			now.QuadPart / m_frequency));

	m_fnStack.push(m_fnCalls.size() - 1);

} // Tracer::Start

void Tracer::End(unsigned frame)
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	while (!m_fnStack.empty())
	{
		FnCall& fnCall = m_fnCalls[m_fnStack.top()];
		m_fnStack.pop();

		if (fnCall.m_frame == frame)
		{
			fnCall.End(now.QuadPart / m_frequency);
			break;
		}
	}

} // Tracer::End

// ============================================================================
//	Hook Functions

void __declspec(naked) _cdecl _penter(void)
{
	_asm
	{
		pushad
		mov eax, esp
		add eax, 32
		push eax

		call Hook::EnterFn

		popad
		ret
	}
}

void __declspec(naked) _cdecl _pexit(void)
{
	_asm
	{
		pushad
		mov eax, esp
		add eax, 32
		push eax

		call Hook::ExitFn

		popad
		ret
	}
}

Logger::Logger()
	:	m_log("instrumentation.log")
{
	m_log << "call\tparent\taddr\telapsed" << std::endl;

} // Logger::Logger

void Logger::Log(const FnCall& fnCall)
{
	m_log << fnCall.m_id << '\t';

	if (fnCall.m_parentId == -1)
		m_log << "N/A";
	else
		m_log << fnCall.m_parentId;

	m_log
		<< '\t'
		<< std::hex
		<< std::setw(8)
		<< std::setfill('0')
		<< fnCall.m_address
		<< std::dec
		<< '\t';

	if (fnCall.Completed())
	{
		m_log
			<< std::setiosflags(std::ios::fixed | std::ios::showpoint)
			<< std::setprecision(3)
			<< fnCall.Duration() * 1000.
			<< std::resetiosflags(std::ios::fixed | std::ios::showpoint);
	}
	else
		m_log << "N/A";

	m_log << std::endl;

} // Logger::Log

std::auto_ptr<Hook> Hook::m_instance (new Hook(new Tracer(new Logger())));
