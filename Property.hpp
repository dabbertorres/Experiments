#include <functional>

namespace swift
{
	template<typename T>
	class Property
	{
		public:
			using Getter = std::function<const T&() const>;
			using Setter = std::function<T&(const T&)>;
			
			Property(T& t, const Getter& get = DefaultGetter, const Setter& set = DefaultSetter);
			~Property() = default;
			
			// getter
			const T& operator ()() const;
			
			// setter
			T& operator =(const T&);
			
		private:
			T& value;
			
			Getter getter;
			Setter setter;
			
			static const Getter DefaultGetter;
			
			static const Setter DefaultSetter;
	};
	
	template<typename T>
	const typename Property<T>::Getter Property<T>::DefaultGetter = [this]() -> const T&
	{
		return this->value;
	};
	
	template<typename T>
	const typename Property<T>::Setter Property<T>::DefaultSetter = [this](const T& t) -> T&
	{
		this->value = t;
		return this->value;
	};
}