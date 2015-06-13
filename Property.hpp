#include <functional>

namespace swift
{
	template<typename T>
	class Property
	{
		public:
			using Getter = std::function<const T&()>;
			using Setter = std::function<T&(const T&)>;

			Property(const Getter& get, const Setter& set);
			~Property() = default;

			// getter
			const T& operator ()() const;

			// setter
			T& operator =(const T&);

			void setGetter(const Getter& get);
			void setSetter(const Setter& set);

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
	const T& Property<T>::operator ()() const
	{
		return getter();
	}

	template<typename T>
	T& Property<T>::operator =(const T& t)
	{
		return setter(t);
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
}
