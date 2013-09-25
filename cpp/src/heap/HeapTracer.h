#ifndef HEAP_HEAPTRACER_H
#define HEAP_HEAPTRACER_H

#include "HeapRequests.h"

namespace Heap
{

// ############################################################################
//	CLASS HeapTracer

class HeapTracer
{

// types
public:

	typedef HeapRequests Snapshot;

	class Observer
	{
	// public interface
	public:

		virtual void OnTypeMismatch (const HeapRequest& request) = 0;

		virtual void OnDoubleFree (void* ptr) = 0;
	};

// constructors
public:

	HeapTracer ();

	~HeapTracer ();

// accessors
public:

	size_t GetQualifiedRequestCount () const
		{ return m_requests.GetCount (HeapRequest::e_qualified); }

	size_t GetUnqualifiedRequestCount () const
		{ return m_requests.GetCount (HeapRequest::e_unqualified); }

// public interface
public:

	void Dump (
		std::ostream& out,
		HeapRequest::RequestType requestType
	);

	void* Register (
		size_t size,
		bool array,
		const char* file,
		int line
	);

	void Unregister (
		void* ptr,
		bool array
	);

	const Snapshot& GetSnapshot ()
		{ return m_requests; }

	void SetObserver (Observer* observer)
		{ m_observer = observer; }

// support methods
protected:

	void StartTracing ()
		{ m_trace = true; }

	void StopTracing ()
	 { m_trace = false; }

// data members
private:

	static bool		m_trace;
	HeapRequests	m_requests;

	Observer*		m_observer;

}; // HeapTracer

} // namespace Heap

#endif // HEAP_HEAPTRACER_H
