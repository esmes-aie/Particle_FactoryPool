#pragma once

template<typename T>
class ObjectPool
{
	struct __intern // interleaved type, Array of Structures (AoS)
	{
		bool     open; // if this index is open
		size_t   next; // next index in this list
		T		 data; // the actual data we are storing	
	};

	__intern *m_data;
	size_t    m_size;

	size_t openHead, fillHead;

public:
	/* Rule of 5 */	
	ObjectPool(const ObjectPool &)			  = delete;
	ObjectPool &operator=(const ObjectPool &) = delete;
	ObjectPool(ObjectPool &&)				  = delete;
	ObjectPool &operator=(ObjectPool &&)	  = delete;

	~ObjectPool() { delete[] m_data; }

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

		T &operator* ()   { return  m_ref->m_data[m_idx].data; } // *this (Dereference operator)
		T *operator->()   { return &m_ref->m_data[m_idx].data; } // this->(Indirection operator)
		T *operator& ()   { return &m_ref->m_data[m_idx].data; } // &this reference-of operator

		const T &operator* () const { return  m_ref->m_data[m_idx].data; } // (constant dereference)
		const T *operator->() const { return &m_ref->m_data[m_idx].data; } // (constant indirection)
		const T *operator& () const { return &m_ref->m_data[m_idx].data; } // &this reference-of operator

		iterator &operator++()   { m_idx = m_ref->m_data[m_idx].next; return *this; } // (prefix increment)
		iterator operator++(int) { auto that = *this;  operator++();  return  that; } // (postfix increment)

		bool operator==(const iterator &O) const { return m_ref == O.m_ref && m_idx == O.m_idx; }
		bool operator!=(const iterator &O) const { return !operator==(O); }

		operator bool() const { return m_ref != nullptr && m_idx < m_ref->m_size && !m_ref->m_data[m_idx].open; }
	
		operator       T*()       { return operator&(); }
		operator const T*() const { return operator&(); }
		
		// Address-of operator	
		iterator &free() { return *this = m_ref->pop(*this); }
	};


	// push the value into the pool and generate an iterator.
	iterator push(const T &val = T())
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

	iterator pop(iterator it)
	{
		if (!(it && it.m_ref == this)) return iterator();

		size_t idx = it.m_idx;
		++it;

		// if we are popping the closed head, we need to update the close list
		// if we are popping left of the vacant head, we need to update the vacant head
		// if there was a closed next pointing to this index, we have to update it.
		m_data[idx].open = true;
		
		/////////////////////////////////////////
		// For fixing the filled list pointers
		if (idx == fillHead)
			fillHead = m_data[idx].next;
		else // there must be a closed index pointing to us.
		{
			size_t left = idx;
			while (m_data[--left].open); // walk left until we hit the thing pointing at us!
			m_data[left].next = m_data[idx].next; // tell it to point at what we were previously pointing to.
		}

		/////////////////////////////////////////
		// For inserting the open space
		if (idx < openHead)
		{
			m_data[idx].next = openHead;
			openHead = idx;
		}
		else // IF there is a vacancy to our left
		{
			size_t left = idx;
			while (!m_data[--left].open);

			m_data[idx].next = m_data[left].next;
			m_data[left].next = idx;
		}
		return it;
	}

	// for each
	iterator begin()  { return iterator(this, fillHead); }
	iterator end()	  { return iterator(this, m_size);   }

	// for(auto it = begin(); it != end(); ++it);
};