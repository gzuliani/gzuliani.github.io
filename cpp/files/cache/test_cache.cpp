#define CHECK(x) \
	if (!(x)) \
	{ \
		std::cerr \
			<< __FILE__ \
			<< "(" \
			<< __LINE__ \
			<< ") : CHECK failed" \
			<< std::endl; \
		exit(-1); \
	}

#include <iostream>
#include <string>

#include "cache.h"

int main()
{
	cache<int, std::string> aCache;

	// cache is initally empty
	CHECK(aCache.empty());
	CHECK(aCache.size() == 0);

	// set cache depth
	CHECK(aCache.depth() == 0);
	aCache.set_depth(3);
	CHECK(aCache.depth() == 3);

	// cache a new item
	aCache.insert(1, "first");
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 1);

	// fetch an item
	cache<int, std::string>::const_iterator entry = aCache.fetch(1);
	CHECK(entry != aCache.end());
	CHECK(*entry == "first");

	// trying to fetch an uncached item is a safe operation
	entry = aCache.fetch(9);
	CHECK(entry == aCache.end());

	// cache a second item
	aCache.insert(2, "second");
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 2);

	// cache a third item
	aCache.insert(3, "third");
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 3);

	// items are stored in reverse order
	entry = aCache.begin();
	CHECK(*entry == "third");
	entry++;
	CHECK(*entry == "second");
	entry++;
	CHECK(*entry == "first");
	entry++;
	CHECK(entry == aCache.end());

	// fetching an item brings it in first postion
	aCache.fetch(2);
	entry = aCache.begin();
	CHECK(*entry == "second");
	entry++;
	CHECK(*entry == "third");
	entry++;
	CHECK(*entry == "first");
	entry++;
	CHECK(entry == aCache.end());

	// reaching the cache limit...
	aCache.insert(4, "fourth");
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 3);
	entry = aCache.begin();
	CHECK(*entry == "fourth");
	entry++;
	CHECK(*entry == "second");
	entry++;
	CHECK(*entry == "third");
	entry++;
	CHECK(entry == aCache.end());

	// remove a cached item
	aCache.remove(2);
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 2);
	entry = aCache.begin();
	CHECK(*entry == "fourth");
	entry++;
	CHECK(*entry == "third");
	entry++;
	CHECK(entry == aCache.end());

	// trying to remove an uncached item is a safe operation
	aCache.remove(9);
	CHECK(!aCache.empty());
	CHECK(aCache.size() == 2);
	entry = aCache.begin();
	CHECK(*entry == "fourth");
	entry++;
	CHECK(*entry == "third");
	entry++;
	CHECK(entry == aCache.end());

	// erase the cache
	aCache.clear();
	CHECK(aCache.empty());
	CHECK(aCache.size() == 0);
	CHECK(aCache.depth() == 3);

	return 0;
}
