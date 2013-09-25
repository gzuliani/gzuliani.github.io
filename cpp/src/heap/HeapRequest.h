#ifndef HEAP_HEAPREQUEST_H
#define HEAP_HEAPREQUEST_H

#include <cstddef>	// size_t

namespace Heap
{

// ############################################################################
//	CLASS HeapRequest

class HeapRequest
{

// types
public:

	enum RequestType
	{
		e_generic,
		e_qualified,
		e_unqualified,
	};

// constructors
public:

	HeapRequest ()
		:	m_size (0), m_array (false), m_file (0), m_line (0)
		{ }

	HeapRequest (size_t size, bool array, const char* file, int line)
		:	m_size (size), m_array (array), m_file (file), m_line (line)
		{ }

// operators
public:

	bool IsQualified () const
		{ return m_file != 0; } 

	bool IsUnqualified () const
		{ return !IsQualified (); } 

	bool operator== (
		const HeapRequest& request
	) const;

	bool operator!= (const HeapRequest& request) const
		{ return !operator== (request); }

// accessors
public:

	size_t GetSize () const
		{ return m_size; }

	bool IsArray () const
		{ return m_array; }

	const char* GetFile () const
		{ return m_file ? m_file : ""; }

	int GetLine () const
		{ return m_line; }

// data members
protected:

	size_t		m_size;
	bool		m_array;
	const char*	m_file;
	int			m_line;

}; // HeapRequest

} // namespace Heap

#endif // HEAP_HEAPREQUEST_H
