#ifndef IMG_RANGED_VALUE_HPP
#define IMG_RANGED_VALUE_HPP

#include <type_traits>
#include <algorithm>

template<typename BaseType, BaseType Min, BaseType Max, typename = typename std::enable_if<std::is_arithmetic<BaseType>::value>::type>
class RangedValue
{
	public:
		RangedValue() = default;
		RangedValue(BaseType val);

		static constexpr BaseType min = Min;
		static constexpr BaseType max = Max;

		// implict cast to base type for arithmetic
		operator BaseType() const;

		// assignments
		RangedValue& operator=(BaseType bt);
		RangedValue& operator=(RangedValue rv);

		RangedValue& operator+=(BaseType bt);
		RangedValue& operator+=(RangedValue rv);

		RangedValue& operator-=(BaseType bt);
		RangedValue& operator-=(RangedValue rv);

		RangedValue& operator*=(BaseType bt);
		RangedValue& operator*=(RangedValue rv);

		RangedValue& operator/=(BaseType bt);
		RangedValue& operator/=(RangedValue rv);

	private:
		BaseType value;
};

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>::RangedValue(BaseType val)
{
	*this = val;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>::operator BaseType() const
{
	return value;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator=(BaseType bt)
{
	value = std::min(Max, std::max(bt, Min));
	return *this;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator=(RangedValue rv)
{
	value = rv.value;
	return *this;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator+=(BaseType bt)
{
	return *this = value + bt;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator+=(RangedValue rv)
{
	return *this += rv.value;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator-=(BaseType bt)
{
	return *this = value - bt;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator-=(RangedValue rv)
{
	return *this -= rv.value;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator*=(BaseType bt)
{
	return *this = value * bt;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator*=(RangedValue rv)
{
	return *this *= rv.value;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator/=(BaseType bt)
{
	return *this = value / bt;
}

template<typename BaseType, BaseType Min, BaseType Max, typename E>
RangedValue<BaseType, Min, Max, E>& RangedValue<BaseType, Min, Max, E>::operator/=(RangedValue rv)
{
	return *this /= rv.value;
}

#endif
