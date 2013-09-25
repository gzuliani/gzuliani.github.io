#include <iostream>

// ============================================================================
//	FUNCTION bomb

void bomb(bool boom)
{
	if (boom)
		throw 1;

} // bomb

// ============================================================================
//	FUNCTION inner

void inner(bool boom)
{
	bomb (boom);

} // inner

// ============================================================================
//	FUNCTION outer

void outer(bool boom)
{
	try
	{
		inner(boom);
	}
	catch(...)
		{ }

} // outer

// ============================================================================
//	FUNCTION recurse

void recurse(unsigned level, bool boom)
{
	if (level > 0)
		recurse(level - 1, boom);
	else if (boom)
		throw 1;

} // recurse

int main()
{
	outer(false);
	outer(true);
	recurse(5, false);

	try
	{
		recurse(5, true);
	}
	catch(...)
		{ }

	return 0;

} // main
