#include "minirt_bonus.h"

double	real_max(double x, double y, double z)
{
	double bigger;

	bigger = x;
	if (y > bigger)
		bigger = y;
	if (z > bigger)
		bigger = z;
	return (bigger);
}
