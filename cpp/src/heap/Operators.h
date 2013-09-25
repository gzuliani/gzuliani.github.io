#ifndef HEAP_OPERATORS_H
#define HEAP_OPERATORS_H

#include "HeapTracer.h"

extern Heap::HeapTracer theHeapTracer_;

// ============================================================================
//	GLOBAL OPERATORS

void* operator new (
	size_t size);

void operator delete (
	void* ptr);

void* operator new [] (
	size_t size);

void operator delete [] (
	void* ptr);

void* operator new (
	size_t size,
	const char* file,
	int line);

void operator delete (
	void* ptr,
	const char* file,
	int line);

void* operator new [] (
	size_t size,
	const char* file,
	int line);

void operator delete [] (
	void* ptr,
	const char* file,
	int line);

#endif // HEAP_OPERATORS_H
