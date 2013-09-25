#include "Operators.h"

using namespace Heap;

// ============================================================================
//	GLOBAL OPERATORS

void* operator new (
	size_t size)
{
	return theHeapTracer_.Register (size, false, 0, 0);

} // operator new

void operator delete (
	void* ptr)
{
	theHeapTracer_.Unregister (ptr, false);

} // operator delete

void* operator new [] (
	size_t size)
{
	return theHeapTracer_.Register (size, true, 0, 0);

} // operator new []

void operator delete [] (
	void* ptr)
{
	theHeapTracer_.Unregister (ptr, true);

} // operator delete []

void* operator new (
	size_t size,
	const char* file,
	int line)
{
	return theHeapTracer_.Register (size, false, file, line);

} // operator new

void operator delete (
	void* ptr,
	const char* file,
	int line)
{
	theHeapTracer_.Unregister (ptr, false);

} // operator delete

void* operator new [] (
	size_t size,
	const char* file,
	int line)
{
	return theHeapTracer_.Register (size, true, file, line);

} // operator new []

void operator delete [] (
	void* ptr,
	const char* file,
	int line)
{
	theHeapTracer_.Unregister (ptr, true);

} // operator delete []
