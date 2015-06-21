#include <functional>
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class DynArray;

template<typename T, typename Alloc = std::allocator<T>>
bool operator ==(const DynArray<T, Alloc>&, const DynArray<T, Alloc>&);

template<typename T, typename Alloc = std::allocator<T>>
bool operator !=(const DynArray<T, Alloc>&, const DynArray<T, Alloc>&);

template<typename T, typename Alloc = std::allocator<T>>
void swap(DynArray<T, Alloc>&, DynArray<T, Alloc>&);

template<typename T, typename Alloc>
class DynArray
{
	public:
		// aliases
		using ReallocCallback = std::function<void(const T const*, std::size_t)>;
		using allocator_type = Alloc;
		using value_type = typename Alloc::value_type;
		using reference = typename Alloc::reference;
		using const_reference = typename Alloc::const_reference;
		using rvalue_reference = T&&;
		using pointer = typename Alloc::pointer;
		using const_pointer = typename Alloc::const_pointer;
		using difference_type = typename Alloc::difference_type;
		using size_type = typename Alloc::size_type;

		class iterator
		{
			public:
				using difference_type = typename Alloc::difference_type;
				using value_type = typename Alloc::value_type;
				using reference = typename Alloc::reference;
				using pointer = typename Alloc::pointer;
				using iterator_category = std::random_access_iterator_tag;

				iterator();
				iterator(pointer ptr);
				iterator(const iterator&);
				~iterator() = default;

				iterator& operator =(const iterator&);

				// query
				operator bool() const;

				// comparisons
				template<T, Alloc>
				friend bool operator ==(const iterator&, const iterator&);

				template<T, Alloc>
				friend bool operator !=(const iterator&, const iterator&);

				template<T, Alloc>
				friend bool operator <(const iterator&, const iterator&);

				template<T, Alloc>
				friend bool operator >(const iterator&, const iterator&);

				template<T, Alloc>
				friend bool operator <=(const iterator&, const iterator&);

				template<T, Alloc>
				friend bool operator >=(const iterator&, const iterator&);

				// iteration
				iterator& operator ++();	// prefix
				iterator operator ++(int);	// postfix
				iterator& operator --();	// prefix
				iterator operator --(int);	// postfix
				iterator& operator +=(size_type);
				iterator& operator -=(size_type);

				template<T, Alloc>
				friend iterator operator +(const iterator&, size_type);

				template<T, Alloc>
				friend iterator operator +(size_type, const iterator&);

				template<T, Alloc>
				friend iterator operator -(const iterator&, size_type);

				// distance between iterators
				template<T, Alloc>
				friend size_type operator -(const iterator&, const iterator&);

				reference operator *();
				const_reference operator *() const;
				pointer operator ->();
				const_pointer operator ->() const;

			private:
				pointer value;
		};

		class const_iterator
		{
			public:
				using difference_type = typename Alloc::difference_type;
				using value_type = typename Alloc::value_type;
				using reference = typename Alloc::const_reference;
				using pointer = typename Alloc::const_pointer;
				using iterator_category = std::random_access_iterator_tag;

				const_iterator();
				const_iterator(pointer ptr);
				const_iterator(const const_iterator&);
				const_iterator(const iterator&);
				~const_iterator() = default;

				const_iterator& operator =(const const_iterator&);
				const_iterator& operator =(const iterator&);

				// query
				operator bool() const;

				// comparisons
				template<T, Alloc>
				friend bool operator ==(const const_iterator&, const const_iterator&);

				template<T, Alloc>
				friend bool operator !=(const const_iterator&, const const_iterator&);

				template<T, Alloc>
				friend bool operator <(const const_iterator&, const const_iterator&);

				template<T, Alloc>
				friend bool operator >(const const_iterator&, const const_iterator&);

				template<T, Alloc>
				friend bool operator <=(const const_iterator&, const const_iterator&);

				template<T, Alloc>
				friend bool operator >=(const const_iterator&, const const_iterator&);

				// iteration
				const_iterator& operator ++();		// prefix
				const_iterator operator ++(int);	// postfix
				const_iterator& operator --();		// prefix
				const_iterator operator --(int);	// postfix
				const_iterator& operator +=(size_type);
				const_iterator& operator -=(size_type);

				template<T, Alloc>
				friend const_iterator operator +(const const_iterator&, size_type);

				template<T, Alloc>
				friend const_iterator operator +(size_type, const const_iterator&);

				template<T, Alloc>
				friend const_iterator operator -(const const_iterator&, size_type);

				// distance between iterators
				template<T, Alloc>
				friend size_type operator -(const const_iterator&, const const_iterator&);

				const_reference operator *() const;
				const_pointer operator ->() const;

			private:
				const_pointer value;
		};

		// constructors
		DynArray();

		// reserving constructor
		DynArray(size_type);

		// sizing constructor
		DynArray(size_type, const_reference);

		// initializer list constructor
		DynArray(std::initializer_list<value_type>);

		// copy constructor
		DynArray(const DynArray&);

		// move constructor
		DynArray(DynArray&&);

		// initializer list operator
		DynArray& operator =(std::initializer_list<value_type>);

		// copy operator
		DynArray& operator =(const DynArray&);

		// move operator
		DynArray& operator =(DynArray&&);

		~DynArray();

		// setup functions
		void setCallback(const ReallocCallback&);

		// comparisons
		friend bool operator ==<T, Alloc>(const DynArray&, const DynArray&);

		friend bool operator !=<T, Alloc>(const DynArray&, const DynArray&);

		// iterators
		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		// access
		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		reference at(size_type);
		const_reference at(size_type) const;

		reference operator [](size_type);
		const_reference operator [](size_type) const;

		pointer data();
		const_pointer data() const;

		// modifying
		template<typename... Args>
		void emplace_front(Args...);

		template<typename... Args>
		void emplace_back(Args...);

		template<typename... Args>
		iterator emplace(const_iterator, Args...);

		iterator insert(const_iterator, const_reference);
		iterator insert(const_iterator, rvalue_reference);
		iterator insert(const_iterator, size_type, reference);

		template<typename iter>
		iterator insert(const_iterator, iter, iter);
		iterator insert(const_iterator, std::initializer_list<value_type>);

		void push_front(const_reference);
		void push_front(rvalue_reference);

		void push_back(const_reference);
		void push_back(rvalue_reference);

		iterator erase(const_iterator);
		iterator erase(const_iterator, const_iterator);

		void pop_front();
		void pop_back();

		void clear();

		template<typename iter>
		void assign(iter, iter);
		void assign(std::initializer_list<value_type>);
		void assign(size_type, const_reference);

		// other operations
		void swap(DynArray&);
		void reserve(size_type);
		void resize(size_type);

		// queries
		size_type size();
		size_type capacity();
		size_type max_size();
		bool empty();

	private:
		// pointer to address of first element
		pointer start;

		// pointer to one past the address of the last element
		pointer last;

		// pointer to one past the last currently allocated address
		pointer lastAddr;

		Alloc allocator;

		// function that gets called every time the begin pointer is moved
		// accepts a pointer (which will be the new begin address)
		// and the current size of the DynArray
		ReallocCallback reallocCallback;

		static constexpr size_type INITIAL_SIZE = 8;
		static constexpr float GROWTH_FACTOR = 2.0;
};

// iterator
template<typename T, typename Alloc>
DynArray<T, Alloc>::iterator::iterator()
:	value(nullptr)
{}

template<typename T, typename Alloc>
DynArray<T, Alloc>::iterator::iterator(pointer ptr)
:	value(ptr)
{}

template<typename T, typename Alloc>
DynArray<T, Alloc>::iterator::iterator(const iterator& other)
:	value(other.value)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator& DynArray<T, Alloc>::iterator::operator =(const iterator& other)
{
	value = other.value;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::iterator::operator bool() const
{
	return value;
}

template<typename T, typename Alloc>
bool operator ==(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value == rhs.value;
}

template<typename T, typename Alloc>
bool operator !=(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
bool operator <(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value < rhs.value;
}

template<typename T, typename Alloc>
bool operator >(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value > rhs.value;
}

template<typename T, typename Alloc>
bool operator <=(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value <= rhs.value;
}

template<typename T, typename Alloc>
bool operator >=(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value >= rhs.value;
}

// prefix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator& DynArray<T, Alloc>::iterator::operator ++()
{
	value += sizeof(value_type);
	return *this;
}

// postfix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::iterator::operator ++(int)
{
	pointer temp = value;
	value += sizeof(value_type);
	return {temp};
}

// prefix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator& DynArray<T, Alloc>::iterator::operator --()
{
	value -= sizeof(value_type);
	return *this;
}

// postfix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::iterator::operator --(int)
{
	pointer temp = value;
	value -= sizeof(value_type);
	return {temp};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator& DynArray<T, Alloc>::iterator::operator +=(size_type n)
{
	value += sizeof(value_type) * n;
	return *this;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator& DynArray<T, Alloc>::iterator::operator -=(size_type n)
{
	value -= sizeof(value_type) * n;
	return *this;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator operator +(const typename DynArray<T, Alloc>::iterator& lhs, typename DynArray<T, Alloc>::size_type rhs)
{
	return {lhs.value + sizeof(typename DynArray<T, Alloc>::value_type) * rhs};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator operator +(typename DynArray<T, Alloc>::size_type lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return rhs + lhs;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator operator -(const typename DynArray<T, Alloc>::iterator& lhs, typename DynArray<T, Alloc>::size_type rhs)
{
	return {lhs.value - sizeof(typename DynArray<T, Alloc>::value_type) * rhs};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::size_type operator -(const typename DynArray<T, Alloc>::iterator& lhs, const typename DynArray<T, Alloc>::iterator& rhs)
{
	return lhs.value - rhs.value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::reference DynArray<T, Alloc>::iterator::operator *()
{
	return *value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::iterator::operator *() const
{
	return *value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::pointer DynArray<T, Alloc>::iterator::operator ->()
{
	return value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_pointer DynArray<T, Alloc>::iterator::operator ->() const
{
	return value;
}

// const_iterator
template<typename T, typename Alloc>
DynArray<T, Alloc>::const_iterator::const_iterator()
:	value(nullptr)
{}

template<typename T, typename Alloc>
DynArray<T, Alloc>::const_iterator::const_iterator(pointer ptr)
:	value(ptr)
{}

template<typename T, typename Alloc>
DynArray<T, Alloc>::const_iterator::const_iterator(const iterator& other)
:	value(other.value)
{}

template<typename T, typename Alloc>
DynArray<T, Alloc>::const_iterator::const_iterator(const const_iterator& other)
:	value(other.value)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator =(const const_iterator& other)
{
	value = other.value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator =(const iterator& other)
{
	value = other.value;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::const_iterator::operator bool() const
{
	return value;
}

template<typename T, typename Alloc>
bool operator ==(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value == rhs.value;
}

template<typename T, typename Alloc>
bool operator !=(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
bool operator <(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value < rhs.value;
}

template<typename T, typename Alloc>
bool operator >(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value > rhs.value;
}

template<typename T, typename Alloc>
bool operator <=(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value <= rhs.value;
}

template<typename T, typename Alloc>
bool operator >=(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value >= rhs.value;
}

// prefix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator ++()
{
	value += sizeof(value_type);
	return *this;
}

// postfix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::const_iterator::operator ++(int)
{
	pointer temp = value;
	value += sizeof(value_type);
	return {temp};
}

// prefix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator --()
{
	value -= sizeof(value_type);
	return *this;
}

// postfix
template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::const_iterator::operator --(int)
{
	pointer temp = value;
	value -= sizeof(value_type);
	return {temp};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator +=(size_type n)
{
	value += sizeof(value_type) * n;
	return *this;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator& DynArray<T, Alloc>::const_iterator::operator -=(size_type n)
{
	value -= sizeof(value_type) * n;
	return *this;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator operator +(const typename DynArray<T, Alloc>::const_iterator& lhs, typename DynArray<T, Alloc>::size_type rhs)
{
	return {lhs.value + sizeof(typename DynArray<T, Alloc>::value_type) * rhs};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator operator +(typename DynArray<T, Alloc>::size_type lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return rhs + lhs;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator operator -(const typename DynArray<T, Alloc>::const_iterator& lhs, typename DynArray<T, Alloc>::size_type rhs)
{
	return {lhs.value - sizeof(typename DynArray<T, Alloc>::value_type) * rhs};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::size_type operator -(const typename DynArray<T, Alloc>::const_iterator& lhs, const typename DynArray<T, Alloc>::const_iterator& rhs)
{
	return lhs.value - rhs.value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::const_iterator::operator *() const
{
	return *value;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_pointer DynArray<T, Alloc>::const_iterator::operator ->() const
{
	return value;
}

// DynArray
template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray()
{
	start = allocator.allocate(INITIAL_SIZE);
	last = start;
	lastAddr = start + sizeof(value_type) * INITIAL_SIZE;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray(size_type n)
{
	start = allocator.allocate(n);
	last = start;
	lastAddr = start + sizeof(value_type) * n;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray(size_type n, const_reference val)
{
	start = allocator.allocate(n);
	last = start + sizeof(value_type) * n;
	lastAddr = last;

	iterator end(last);
	for(iterator it(start); it != end; ++it)
		*it = val;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray(std::initializer_list<value_type> ilist)
{
	constexpr auto size = ilist.size();

	start = allocator.allocate(size);
	last = start + sizeof(value_type) * size;
	lastAddr = last;

	iterator it(start);
	for(auto ilistIt = ilist.begin(); ilistIt != ilist.end(); ++ilistIt, ++it)
		*it = *ilistIt;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray(const DynArray& other)
{
	constexpr auto size = other.size();

	start = allocator.allocate(size);
	last = start + sizeof(value_type) * size;
	lastAddr = last;

	iterator it(start);
	iterator end(other.last);
	for(iterator otherIt(other.start); otherIt != end; ++otherIt, ++it)
		*it = *otherIt;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::DynArray(DynArray&& other)
:	allocator(std::move(other.allocator))
{
	start = other.start;
	last = other.last;
	lastAddr = other.lastAddr;

	other.start = nullptr;
	other.last = nullptr;
	other.lastAddr = nullptr;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>::~DynArray()
{
	if(start && last)
	{
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));
	}
}

template<typename T, typename Alloc>
DynArray<T, Alloc>& DynArray<T, Alloc>::operator =(std::initializer_list<value_type> ilist)
{
	constexpr auto ilistSize = ilist.size();

	// if we can fit the ilist in our already allocated memory, don't allocate
	if(ilist.size() <= (lastAddr - start) / sizeof(value_type))
	{
		iterator it(start);
		for(auto ilistIt = ilist.begin(); ilistIt != ilist.end(); ++ilistIt, ++it)
			*it = *ilistIt;

		last = it;
	}
	// if not, then reallocate
	else
	{
		if(start && lastAddr)
			allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		start = allocator.allocate(ilistSize);
		last = start + sizeof(value_type) * ilistSize;
		lastAddr = last;

		// if we have a reallocation callback, call it with the new data
		if(reallocCallback)
			reallocCallback(start, (last - start) / sizeof(value_type));

		iterator it(start);
		for(auto ilistIt = ilist.begin(); ilistIt != ilist.end(); ++ilistIt, ++it)
			*it = *ilistIt;
	}

	return *this;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>& DynArray<T, Alloc>::operator =(const DynArray& other)
{
	constexpr auto otherSize = other.size();

	if(otherSize <= (lastAddr - start) / sizeof(value_type))
	{
		iterator it(start);
		for(auto otherIt = other.begin(); otherIt != other.end(); ++otherIt, ++it)
			*it = *otherIt;

		last = it;
	}
	else
	{
		if(start && lastAddr)
			allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		start = allocator.allocate(otherSize);
		last = start + sizeof(value_type) * otherSize;
		lastAddr = last;

		// if we have a reallocation callback, call it with the new data
		if(reallocCallback)
			reallocCallback(start, (last - start) / sizeof(value_type));

		iterator it(start);
		for(auto otherIt = other.begin(); otherIt != other.end(); ++otherIt, ++it)
			*it = *otherIt;
	}

	return *this;
}

template<typename T, typename Alloc>
DynArray<T, Alloc>& DynArray<T, Alloc>::operator =(DynArray&& other)
{
	// deallocate our current memory if needed
	if(start && lastAddr)
		allocator.deallocate((lastAddr - start) / sizeof(value_type));

	allocator = std::move(other.allocator);
	start = other.start;
	last = other.last;
	lastAddr = other.lastAddr;

	other.start = nullptr;
	other.last = nullptr;
	other.lastAddr = nullptr;
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::setCallback(const ReallocCallback& rc)
{
	reallocCallback = rc;
}

template<typename T, typename Alloc>
bool operator ==(const DynArray<T, Alloc>& lhs, const DynArray<T, Alloc>& rhs)
{
	return lhs.start == rhs.start && lhs.last == rhs.last && lhs.lastAddr == rhs.lastAddr;
}

template<typename T, typename Alloc>
bool operator !=(const DynArray<T, Alloc>& lhs, const DynArray<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::begin()
{
	return {start};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::begin() const
{
	return {start};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::cbegin() const
{
	return {start};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::end()
{
	return {end};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::end() const
{
	return {end};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_iterator DynArray<T, Alloc>::cend() const
{
	return {end};
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::reference DynArray<T, Alloc>::front()
{
	return *start;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::front() const
{
	return *start;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::reference DynArray<T, Alloc>::back()
{
	return *(last - sizeof(value_type));
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::back() const
{
	return *(last - sizeof(value_type));
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::reference DynArray<T, Alloc>::at(size_type n)
{
	return *(start + sizeof(value_type) * n);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::at(size_type n) const
{
	return *(start + sizeof(value_type) * n);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::reference DynArray<T, Alloc>::operator [](size_type n)
{
	return *(start + sizeof(value_type) * n);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_reference DynArray<T, Alloc>::operator [](size_type n) const
{
	return *(start + sizeof(value_type) * n);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::pointer DynArray<T, Alloc>::data()
{
	return start;
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::const_pointer DynArray<T, Alloc>::data() const
{
	return start;
}

template<typename T, typename Alloc>
template<typename... Args>
void DynArray<T, Alloc>::emplace_front(Args... args)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart + sizeof(value_type));	// we're emplacing on the front, so skip the first available
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		// put new element at the front
		new (newStart) value_type(args...);

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}
	// if we don't, just shift everything up
	else
	{
		iterator f(start);
		iterator it(last);
		for(; it != f; --it)
			new (it.operator ->()) value_type(*(it - 1));

		// shift last up 1
		last += sizeof(value_type);

		// now create new element
		new (start) value_type(args...);
	}
}

template<typename T, typename Alloc>
template<typename... Args>
void DynArray<T, Alloc>::emplace_back(Args... args)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart);
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}

	// now add new element
	new (last) value_type(args...);

	// shift last up 1
	last += sizeof(value_type);
}

template<typename T, typename Alloc>
template<typename... Args>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::emplace(const_iterator, Args...)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::insert(const_iterator, const_reference)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::insert(const_iterator, rvalue_reference)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::insert(const_iterator, size_type, reference)
{}

template<typename T, typename Alloc>
template<typename iter>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::insert(const_iterator, iter, iter)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::insert(const_iterator, std::initializer_list<value_type>)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::push_front(const_reference ref)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart + sizeof(value_type));	// we're emplacing on the front, so skip the first available
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		// put new element at the front
		new (newStart) value_type(ref);

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}
	// if we don't, just shift everything up
	else
	{
		iterator f(start);
		iterator it(last);
		for(; it != f; --it)
			new (it.operator ->()) value_type(*(it - 1));

		// shift last up 1
		last += sizeof(value_type);

		// now create new element
		new (start) value_type(ref);
	}
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::push_front(rvalue_reference rref)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart + sizeof(value_type));	// we're emplacing on the front, so skip the first available
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		// put new element at the front
		new (newStart) value_type(rref);

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}
	// if we don't, just shift everything up
	else
	{
		iterator f(start);
		iterator it(last);
		for(; it != f; --it)
			new (it.operator ->()) value_type(*(it - 1));

		// shift last up 1
		last += sizeof(value_type);

		// now create new element
		new (start) value_type(rref);
	}
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::push_back(const_reference ref)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart);
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}

	// now add new element
	new (last) value_type(ref);

	// shift last up 1
	last += sizeof(value_type);
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::push_back(rvalue_reference rref)
{
	// reallocate if we need to
	if(last == lastAddr)
	{
		const auto size = (last - start) / sizeof(value_type);
		const auto newSize = size * GROWTH_FACTOR;

		// get our new memory
		pointer newStart = allocator.allocate(newSize);
		pointer newLast = newStart;
		pointer newLastAddr = newStart + sizeof(value_type) * newSize;

		// copy current elements to new memory
		iterator f(start);
		iterator it(start);
		iterator newIt(newStart);
		iterator end(last);
		for(; it != end; ++it, ++newIt)
			*newIt = *it;

		// get it's pointer value
		newLast = it.operator ->();

		// get rid of old memory
		allocator.deallocate(start, (lastAddr - start) / sizeof(value_type));

		start = newStart;
		last = newLast;
		lastAddr = newLastAddr;
	}

	// now add new element
	new (last) value_type(rref);

	// shift last up 1
	last += sizeof(value_type);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::erase(const_iterator)
{}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::iterator DynArray<T, Alloc>::erase(const_iterator, const_iterator)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::pop_front()
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::pop_back()
{
	last -= sizeof(value_type);
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::clear()
{
	last = start;
}

template<typename T, typename Alloc>
template<typename iter>
void DynArray<T, Alloc>::assign(iter, iter)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::assign(std::initializer_list<value_type>)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::assign(size_type, const_reference)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::swap(DynArray&)
{}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::reserve(size_type n)
{
	const auto cap = (lastAddr - start) / sizeof(value_type);
	if(n <= cap)
		return;

	if(start && lastAddr)
		allocator.deallocate(start, cap);

	start = allocator.allocate(n);
	last = start;
	lastAddr = start + sizeof(value_type) * n;
}

template<typename T, typename Alloc>
void DynArray<T, Alloc>::resize(size_type n)
{
	const auto size = (last - start) / sizeof(value_type);
	const auto cap = (lastAddr - start) / sizeof(value_type);

	if(n <= cap)
		last = start + sizeof(value_type) * n;
	else
	{
		if(start && lastAddr)
			allocator.deallocate(start, cap);

		start = allocator.allocate(n);
		last = start + sizeof(value_type) * n;
		lastAddr = last;
	}
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::size_type DynArray<T, Alloc>::size()
{
	return (last - start) / sizeof(value_type);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::size_type DynArray<T, Alloc>::capacity()
{
	return (lastAddr - start) / sizeof(value_type);
}

template<typename T, typename Alloc>
typename DynArray<T, Alloc>::size_type DynArray<T, Alloc>::max_size()
{
	return size_type::max();
}

template<typename T, typename Alloc>
bool DynArray<T, Alloc>::empty()
{
	return start == last;
}

template<typename T, typename Alloc>
void swap(DynArray<T, Alloc>&, DynArray<T, Alloc>&)
{}
