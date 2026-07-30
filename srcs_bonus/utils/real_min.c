#include "minirt_bonus.h"

REAL	real_min(REAL x, REAL y, REAL z)
{
	REAL less;

	less = x;
	if (y < less)
		less = y;
	if (z < less)
		less = z;
	return (less);
}
