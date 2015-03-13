#ifndef HEAP_HEAPREQUESTS_H
#define HEAP_HEAPREQUESTS_H

#include "HeapRequest.h"

#include <iostream>

namespace Heap
{

// ############################################################################
//	CLASS HeapRequests

class HeapRequests
{

	friend class HeapTracer;

// types
protected:

	struct Request
	{
		void*		ptr;
		HeapRequest	data;
		Request*	next;
	};

// constructors
public:

	HeapRequests ()
		:	m_head (0)
		{ }

	HeapRequests (const HeapRequests& requests)
		:	m_head (0)
		{ operator= (requests); }

	~HeapRequests ()
	{
		Empty ();
		Request* request = m_head;

		while (request)
		{
			Request* tmp = request;
			request = request->next;
			free (tmp);
		}
	}

// operators
public:

	HeapRequests& operator= (const HeapRequests& requests)
	{
		Empty ();
		Request* request = requests.m_head; 

		while (request)
		{
			Insert (request->ptr, request->data);
			request = request->next;
		}

		return *this;
	}

	bool operator== (const HeapRequests& requests) const
	{
		Request* request1 = m_head;
		Request* request2 = requests.m_head;

		while (request1 && request2)
		{
			if ((request1->ptr != request2->ptr)
				|| (request1->data != request2->data))
			break;

			request1 = request1->next;
			request2 = request2->next;
		}

		return !request1 && !request2;
	}

	bool operator!= (const HeapRequests& requests) const
		{ return !operator== (requests); }

// public interface
public:

	size_t GetCount (HeapRequest::RequestType type) const
	{
		size_t count = 0;

		for (Request* request = m_head; request; request = request->next)
		{
			HeapRequest data = request->data;

			switch (type)
			{
				case HeapRequest::e_generic:
					count++;
					break;

				case HeapRequest::e_qualified:
					count += data.IsQualified () ? 1 : 0;
					break;

				case HeapRequest::e_unqualified:
					count += data.IsUnqualified () ? 1 : 0;
					break;
			}
		}

		return count;
	}

	void Dump (
		std::ostream& out,
		HeapRequest::RequestType type
	) const;

// support methods
protected:

	bool Insert (void* ptr, const HeapRequest& data)
	{
		if (Find (ptr))
			return false;

		Request* request =
			reinterpret_cast<Request*> (malloc (sizeof (Request)));

		request->ptr = ptr;
		request->data = data;
		request->next = 0;

		Request** pos = &m_head;

		while (*pos)
			pos = &((*pos)->next);

		*pos = request;
		return true;
	}

	bool Remove (void* ptr)
	{
		Request* prev = 0;
		Request* request = Find (ptr, &prev);

		if (!request)
			return false;

		if (request == m_head)
			m_head = request->next;
		else
			prev->next = request->next;

		free (request);
		return true;
	}

	Request* Find (void* ptr, Request** prev = 0)
	{
		Request* request = m_head;

		if (prev)
			*prev = 0;

		while (request)
		{
			if (request->ptr == ptr)
				break;

			if (prev)
				*prev = request;

			request = request->next;
		}

		return request;
	}

	void Empty ()
	{
		Request* request = m_head;

		while (request)
		{
			Request* tmp = request;
			request = request->next;
			free (tmp);
		}

		m_head = 0;
	}

// data members
private:

	Request*	m_head;

}; // HeapRequests

} // namespace Heap

#endif // HEAP_HEAPREQUESTS_H
