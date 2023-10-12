#include <cmath>

#ifdef FUNCDEG_EXPORTS
#define FUNCDEG_API __declspec(dllexport)
#else
#define FUNCDEG_API __declspec(dllimport)
#endif // FUNCDEG_EXPORTS

extern "C" FUNCDEG_API double func(double left, double right);
double func(double left, double right)
{
	return pow(left, right);
}