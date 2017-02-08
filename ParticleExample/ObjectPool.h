#pragma once

#include "particle.h"

class ObjectPool
{
	struct __intern // interleaved type, Array of Structures (AoS)
	{
		bool     open; // if this index is open
		size_t   next; // next index in this list
		particle data; // the actual data we are storing	
	};

	__intern *m_data; // array of underlying raw data.

	// three parallel arrays? Structure of Arrays (SoA)
	//bool     *m_open;
	//particle *m_data;
	//size_t   *m_next;

	size_t    m_size;

public:
	ObjectPool(size_t a_size) : m_size(a_size)
	{
		m_data = new __intern[m_size];

		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].open = true;
			m_data[i].next = i + 1;
		}
	}

	class iterator // faux pointer
	{
		ObjectPool *m_ref;
		size_t	    m_idx;
	
		friend class ObjectPool;

		// ONLY the object pool can properly construct an iterator.
		iterator(ObjectPool *a_ref, size_t a_idx) : m_ref(a_ref), m_idx(a_idx) {}
	public:
		iterator() : m_ref(nullptr), m_idx(0) { }

		particle &operator* ()   { return  m_ref->m_data[m_idx].data; } // *this (Dereference operator)
		particle *operator->()   { return &m_ref->m_data[m_idx].data; } // this->(Indirection operator)

		const particle &operator* () const { return  m_ref->m_data[m_idx].data; } // (constant dereference)
		const particle *operator->() const { return &m_ref->m_data[m_idx].data; } // (constant indirection)

		iterator &operator++()   { m_idx = m_ref->m_data[m_idx].next; return *this; } // (prefix increment)
		iterator operator++(int) { auto that = *this;  operator++();  return  that; } // (postfix increment)

		bool operator==(const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!=(const iterator &O) const { return !operator==(O); }

		operator bool() const { m_ref != nullptr && m_idx < m_ref->m_size && !m_ref->m_data[m_idx].open; }
	};




	// 3 things that a pool NEEDS to provide:
		// iterator
		// Popping or erasing function
		// pushing or inserting function		
};