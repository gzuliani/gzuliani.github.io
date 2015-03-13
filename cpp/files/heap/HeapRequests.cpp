#include "HeapRequests.h"

#include <iomanip>
#include <ios>

using namespace Heap;

// ############################################################################
//	CLASS HeapRequests

void HeapRequests::Dump (
	std::ostream& out,
	HeapRequest::RequestType type) const
{
	out << "dumping ";

	switch (type)
	{
		case HeapRequest::e_qualified:
			out << "qualified";
			break;
		case HeapRequest::e_unqualified:
			out << "unqualified";
			break;
		default:
			out << "generic";
	}

	out << " memory allocations..." << std::endl;

	int count = 0;
	size_t amount = 0;
	Request* request = m_head;

	for (; request; request = request->next)
	{
		void* ptr = request->ptr;
		HeapRequest data = request->data;

		if (((type == HeapRequest::e_unqualified) && data.IsQualified ())
			|| ((type == HeapRequest::e_qualified) && data.IsUnqualified ()))
			continue;

		size_t size = data.GetSize ();

		out << "request #" << ++count << std::endl;
		out << "address....: " << ptr << std::endl;
		out << "size.......: "<< size << " bytes" << std::endl;
		out << "type.......: "
			<< (data.IsArray () ? "array" : "single") << std::endl;
		out << "location...: ";

		if (data.IsQualified ())
			out << data.GetFile () << ": " << data.GetLine ();
		else	
			out << "N/A";

		out << std::endl;
		out << "contents...: ";
		unsigned char* contents = static_cast<unsigned char*> (ptr);

		const size_t dumpMaxSize = 16;
		out << std::hex << std::setfill ('0');

		for (size_t i = 0; i < std::min (size, dumpMaxSize); i++)
			out << std::setw (2) << static_cast<int> (*(contents + i));

		for (size_t i = size; i < dumpMaxSize; i++)
			out << "--";

		out << " ";
		out << std::dec << std::setfill (' ');

		for (size_t i = 0; i < std::min (size, dumpMaxSize); i++)
		{
			unsigned char c = *(contents + i);
			out << static_cast<char> ((c > 0x1f) && (c < 0x80) ? c : '.');
		}

		for (size_t i = size; i < dumpMaxSize; i++)
			out << "-";

		out << std::endl;
		amount += size;
	}

	out << amount << " bytes allocated in ";
	out << count << " requests." << std::endl;

} // HeapRequests::Dump
