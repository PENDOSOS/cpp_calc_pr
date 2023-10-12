#pragma once

#include <iostream>

#define EPSILON 0.0001

 
class Number
{
public:
    Number(double i) : value(i) {};
    friend const Number operator+(Number const& left, Number const& right);
    friend const Number operator-(Number const& left, Number const& right);
    friend const Number operator*(Number const& left, Number const& right);
    friend const Number operator*=(Number const& left, Number const& right);
    friend const Number operator/(Number const& left, Number const& right);
    friend const std::ostream& operator<<(std::ostream& os, Number const& value);

    double value;
};
