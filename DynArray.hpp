
namespace swift
{
	template<typename T, typename Alloc>
	class DynArray
	{
		public:
			using ReallocCallback = std::function<void(T*, std::size_t)>;
			
			// constructors
			DynArray() = default;
			DynArray(std::size_t size);
			DynArray(std::size_t size, const T& init);
			
			// initializer list constructor
			DynArray(std::initializer_list<T> initList);
			
			// copy constructor
			DynArray(const DynArray& other);
			
			// move constructor
			DynArray(DynArray&& other);
			
			void setCallback(const ReallocCallback& rc);
			
		private:
			T* begin;
			T* end;
			
			Alloc allocator;
			
			// function that gets called every time the begin pointer is moved
			// accepts a pointer (which will be the new begin address)
			// and the current size of the DynArray
			ReallocCallback reallocCallback;
	};
}