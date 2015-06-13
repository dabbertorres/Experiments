#include <functional>

namespace swift
{
	template<typename T>
	class Property
	{
		public:
			using Getter = std::function<const T&(const Property&)>;
			using Setter = std::function<void(Property<T>&, const T&)>;

			Property(T& t, const Getter& get = DefaultGetter, const Setter& set = DefaultSetter);
			~Property() = default;

			// getter
			const T& operator ()() const;

			// setter
			T& operator =(const T&);

			void setGetter(const Getter& get);
			void setSetter(const Setter& set);

		private:
			T& value;

			Getter getter;
			Setter setter;

			static const Getter DefaultGetter;

			static const Setter DefaultSetter;
	};

	template<typename T>
	Property<T>::Property(T& t, const Getter& get, const Setter& set)
	:	value(t),
		getter(get),
		setter(set)
	{}

	template<typename T>
	const T& Property<T>::operator ()() const
	{
		return getter(*this);
	}

	template<typename T>
	T& Property<T>::operator =(const T& t)
	{
		setter(*this, t);
		return value;
	}

	template<typename T>
	void Property<T>::setGetter(const Getter& get)
	{
		getter = get;
	}

	template<typename T>
	void Property<T>::setSetter(const Setter& set)
	{
		setter = set;
	}

	template<typename T>
	const typename Property<T>::Getter Property<T>::DefaultGetter = [](const Property<T>& p) -> const T&
	{
		return p.value;
	};

	template<typename T>
	const typename Property<T>::Setter Property<T>::DefaultSetter = [](Property<T>& p, const T& t)
	{
		p.value = t;
	};
}
