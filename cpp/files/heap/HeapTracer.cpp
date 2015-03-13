#include "HeapTracer.h"

#include "HeapRequest.h"

using namespace Heap;

// ############################################################################
//	CLASS HeapTracer

bool HeapTracer::m_trace = false;

HeapTracer::HeapTracer ()
	:	m_observer (0)
{
	StartTracing ();

} // HeapTracer::HeapTracer

HeapTracer::~HeapTracer ()
{
	StopTracing ();

} // HeapTracer::~HeapTracer

void HeapTracer::Dump (
	std::ostream& out,
	HeapRequest::RequestType requestType)
{
	m_requests.Dump (out, requestType);

} // HeapTracer::Dump

void* HeapTracer::Register (
	size_t size,
	bool array,
	const char* file,
	int line)
{
	void* ptr = malloc (size);

	if (ptr == NULL)
		throw std::bad_alloc ();

	HeapRequest request (size, array, file, line);

	if (!m_requests.Insert (ptr, request))
		throw std::bad_alloc ();

	return ptr;

} // HeapTracer::Register

void HeapTracer::Unregister (
	void* ptr,
	bool array)
{
	HeapRequests::Request* entry = m_requests.Find (ptr);

	if (entry)
	{
		const HeapRequest& request = entry->data;

		if (request.IsArray () == array)
			m_requests.Remove (ptr);
		else
		{
			if (m_observer)
				m_observer->OnTypeMismatch (request);

			ptr = NULL;
		}
	}
	else
	{
		if (m_observer)
			m_observer->OnDoubleFree (ptr);

		ptr = NULL;
	}

	if (ptr != NULL)
		free (ptr);

} // HeapTracer::Unregister
