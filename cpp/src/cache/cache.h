#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <list>
#include <algorithm>
using namespace std;

template<typename key_type, typename cachable_type> 
class cache
{
// types
private:
	typedef map<key_type, cachable_type>	type_map;
	typedef list<key_type>					type_list;

public:
	class const_iterator
	{
	friend class cache;

	// types
	public:
		typedef cachable_type value_type;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;

	// ctors/dtor
	public:
		// --------------------------------------------------
		// default constructor
		const_iterator() { }

		// --------------------------------------------------
		// copy constructor
		const_iterator(const const_iterator& other)
			:	m_position(other.m_position),
				m_cache(other.m_cache)
			{ }

		// --------------------------------------------------
		// other constructors
		const_iterator(typename type_list::iterator p, type_map& c)
			: m_position(p), m_cache(c)
			{ }

		// --------------------------------------------------
		// destructor
		~const_iterator() 
			{ }

	// operators
	public:
		// --------------------------------------------------
		// deferencing operator
		const_reference operator*()
			{ return (*m_cache.find(*m_position)).second; }

		// --------------------------------------------------
		// deferencing operator
		const_pointer operator->()
			{ return &((*m_cache.find(*m_position)).second); }

		// --------------------------------------------------
		// prefix increment operator
		const_iterator& operator++()
		{	
			m_position++;
			return *this;
		}

		// --------------------------------------------------
		// postfix increment operator
		const_iterator operator++(int)
		{	
			const_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		// --------------------------------------------------
		// assignment operator
		const_iterator& operator=(const const_iterator& other)
		{
			m_position = other.m_position;
			m_cache = other.m_cache;
			return *this;
		}

		// --------------------------------------------------
		// equality operator
		bool operator==(const const_iterator& other)
			{ return m_position == other.m_position; }

		bool operator!=(const const_iterator& other)
			{ return !(*this == other); }
	
	// members
	private:
		type_map&						m_cache;
		typename type_list::iterator	m_position;
	};

// ctors/dtor
public:
	// ------------------------------------------------------------
	// default constructor
	cache() : m_depth(0) { }
	
	// ------------------------------------------------------------
	// copy constructor
	cache(const cache& other)
	{
		m_cache = other.m_cache;
		m_lru = other.m_lru;
		m_depth = other.m_depth;
	}

	// ------------------------------------------------------------
	// destructor
	virtual ~cache()
		{ }

// operators
public:
	// ------------------------------------------------------------
	// assignment operator
	const cache& operator=(const cache& other)
	{
		m_cache = other.m_cache;
		m_lru = other.m_lru;
		m_depth = other.m_depth;
		return *this;
	}

// accessors
public:
	// ------------------------------------------------------------
	// sets the cache depth
	void set_depth(unsigned long depth)
	{
		m_depth = depth;
//		resize();
	}

	// ------------------------------------------------------------
	// returns the cache depth
	unsigned long depth() const
		{ return m_depth; }

// methods
public:
	// ------------------------------------------------------------
	// returns an iterator that points to the first cachable
	const_iterator begin()
		{ return const_iterator(m_lru.begin(), m_cache); }
	
	// ------------------------------------------------------------
	// returns an iterator that points just beyond the last cachable
	const_iterator end()
		{ return const_iterator(m_lru.end(), m_cache); }

	// ------------------------------------------------------------
	// checks whether the cache is empty
	bool empty() const
		{ return m_lru.empty(); }

	// ------------------------------------------------------------
	// returns the cache's size
	unsigned long size() const
		{ return m_lru.size(); }

	// ------------------------------------------------------------
	// empties the cache
	void clear()
	{
		m_lru.erase(m_lru.begin(), m_lru.end());
		m_cache.erase(m_cache.begin(), m_cache.end());
	}

	// ------------------------------------------------------------
	// caches the given cachable
	void insert(
		const key_type& key,
		const cachable_type& cachable)
	{
		type_map::iterator cached = m_cache.find(key);

		if (cached == m_cache.end())
		{
			// new element
			m_cache.insert(type_map::value_type(key, cachable));
			m_lru.push_front(key);

			resize();
		}
		else
		{
			// already-cached element
			(*cached).second = cachable;
			type_list::iterator pos = find(m_lru.begin(), m_lru.end(), key);
			m_lru.erase(pos);
			m_lru.push_front(key);
		}
	}

	// ------------------------------------------------------------
	// removes the given cachable
	void remove(const key_type& key)
	{
		type_map::iterator cached = m_cache.find(key);

		if (cached != m_cache.end())
		{
			m_cache.erase(cached);
			type_list::iterator pos = find(m_lru.begin(), m_lru.end(), key);
			m_lru.erase(pos);
		}
	}

	// ------------------------------------------------------------
	// retrieves the requested cachable
	const_iterator fetch(const key_type& key)
	{
		type_list::iterator pos = m_lru.end();
		type_map::iterator cached = m_cache.find(key);

		if (cached != m_cache.end())
		{
			pos = find(m_lru.begin(), m_lru.end(), (*cached).first);
			m_lru.erase(pos);
			m_lru.push_front((*cached).first);
			pos = m_lru.begin();
		}

		return const_iterator(pos, m_cache);
	}

private:
	// ------------------------------------------------------------
	// resizes the cache to the required depth
	void resize()
	{
		if (m_depth > 0)
		{
			while (m_lru.size() > m_depth)
			{
				m_cache.erase(m_lru.back());
				m_lru.pop_back();
			}
		}
	}

// members
private:
	type_map		m_cache;
	type_list		m_lru;
	unsigned long	m_depth;
};

#endif // CACHE_H
