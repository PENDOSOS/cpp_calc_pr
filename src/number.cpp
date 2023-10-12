#include "number.h"

 
const Number operator+(Number const& left, const Number& right) 
{
	return Number(left.value + right.value);
}

const Number operator-(const Number& left, const Number& right) 
{
	return Number(left.value - right.value);
}

const std::ostream& operator<<(std::ostream& os, const Number& value)
{
	os << value.value;
	return os;
}

const Number operator*(const Number& left, const Number& right) 
{
	return Number(left.value * right.value);
}

const Number operator*=(Number& left, const Number& right)
{
	left.value *= right.value;
	return Number(left.value *= right.value);
}

const Number operator/(const Number& left, const Number& right)
{
	if (fabs(right.value) > EPSILON)
		return Number(left.value / right.value);
	else
		return Number(INFINITY);
}