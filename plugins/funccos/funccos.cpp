#include "pch.h"
#include <cmath>

#define PI 3.14

extern "C" __declspec(dllexport) double func(double left, double right = 0)
{
	return cos(left * PI / 180);
}