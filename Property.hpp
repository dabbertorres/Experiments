#include <functional>

template<typename T>
class Property
{
	public:
		using Getter = std::function<const T&()>;
		using Setter = std::function<T&(const T&)>;

		Property(const Getter& get, const Setter& set);
		~Property() = default;

		// getter
		operator const T&() const;

		// setter
		T& operator =(const T&);

	private:
		Getter getter;
		Setter setter;
};

template<typename T>
Property<T>::Property(const Getter& get, const Setter& set)
:	getter(get),
	setter(set)
{}

template<typename T>
Property<T>::operator const T&() const
{
	return getter();
}

template<typename T>
T& Property<T>::operator =(const T& t)
{
	return setter(t);
}
