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

	__intern *m_data;
	size_t    m_size;

	size_t openHead, fillHead;

public:
	ObjectPool(size_t a_size) : m_size(a_size), openHead(0), fillHead(m_size)
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


	// push the value into the pool and generate an iterator.
	iterator push(const particle &val = particle())
	{
		if (openHead >= m_size) return iterator();

		size_t idx = openHead;

		m_data[idx].data = val;
		m_data[idx].open = false;
		
		openHead = m_data[openHead].next;

		if (idx < fillHead) // if we get inserted before the head, become head
		{
			m_data[idx].next = fillHead;
			fillHead = idx;
		}
		else // otherwise there MUST be something filled to our left
		{
			size_t left = idx;
			// this will be closed when the loop stops.
			while (m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}
		return iterator(this, idx);
	}



	iterator pop(const iterator &it);
	// 3 things that a pool NEEDS to provide:
		// iterator
		// Popping or erasing function
		// pushing or inserting function		
};