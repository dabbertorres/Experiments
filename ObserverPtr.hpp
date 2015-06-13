
template<typename T>
class ObserverPtr
{
	public:
		ObserverPtr(T* t, T* start);
		~ObserverPtr() = default;
	
	private:
		T* observed;
		std::size_t observedIndex;
		T* indexZero;
};