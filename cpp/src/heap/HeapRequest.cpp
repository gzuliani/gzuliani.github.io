#include "HeapRequest.h"

using namespace Heap;

// ############################################################################
//	CLASS HeapRequest

bool HeapRequest::operator== (
	const HeapRequest& request) const
{
	return (m_size == request.m_size)
		&& (m_array == request.m_array)
		&& (m_file == request.m_file)
		&& (m_line == request.m_line);

} // HeapRequest::operator==
