#include "minirt_bonus.h"

REAL	real_max(REAL x, REAL y, REAL z)
{
	REAL bigger;

	bigger = x;
	if (y > bigger)
		bigger = y;
	if (z > bigger)
		bigger = z;
	return (bigger);
}
