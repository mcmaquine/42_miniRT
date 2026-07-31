#include "minirt_bonus.h"

double	real_min(double x, double y, double z)
{
	double less;

	less = x;
	if (y < less)
		less = y;
	if (z < less)
		less = z;
	return (less);
}
