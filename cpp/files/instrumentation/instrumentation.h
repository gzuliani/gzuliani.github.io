#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

#include <fstream>
#include <stack>
#include <vector>

using namespace std;

namespace Instrumentation
{

// ############################################################################
//	CLASS Hook

class Hook
{

// types
public:

	class Observer
	{
	// public interface
	public:

		virtual ~Observer();

		virtual void Start(unsigned frame) = 0;

		virtual void End(unsigned frame) = 0;

	}; // Observer

// ctors/dtors
public:

	Hook(Observer* observer);

	~Hook();

// support methods
protected:

	static void _stdcall EnterFn(unsigned frame);

	static void _stdcall ExitFn(unsigned frame);

// data members
private:

	static std::auto_ptr<Hook>	m_instance;

	bool						m_enabled;
	Observer*					m_observer;

}; // Hook

// ############################################################################
//	STRUCT FnCall

struct FnCall
{

// ctors/dtors
public:

	FnCall(size_t id, size_t parentId, unsigned frame, double start);

// accessors
public:

	bool Completed() const;

	double Duration() const;

// public interface
public:

	void End(double end);

// data members
public:

	size_t		m_id;
	size_t		m_parentId;
	unsigned	m_frame;
	unsigned	m_address;
	double		m_start;
	double		m_end;

}; // FnCall

// ############################################################################
//	CLASS Tracer

class Tracer : public Hook::Observer
{

// types
public:

	class Logger
	{

	// ctors/dtors
	public:

		virtual ~Logger();

		virtual void Log(const FnCall& fnCall) = 0;

	};

// ctors/dtors
public:

	Tracer(Logger* logger);

	virtual ~Tracer();

// ctors/dtors
public:

	virtual void Start(unsigned frame);

	virtual void End(unsigned frame);

public:

	double				m_frequency;
	std::vector<FnCall>	m_fnCalls;
	std::stack<size_t>	m_fnStack;

	Logger*				m_logger;

}; // Tracer

class Logger : public Tracer::Logger
{

// ctors/dtors
public:

	Logger();

// Tracer::Logger interface
public:

	virtual void Log(const FnCall& fnCall);

// data members
private:

	std::ofstream	m_log;

}; // Logger

}

// ============================================================================================
//	Hook Functions

extern "C"
{

void _penter(void);

void _pexit(void);

}

#endif // INSTRUMENTATION_H
