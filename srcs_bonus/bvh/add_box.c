#include "minirt_bonus.h"

t_aabb	sphere_aabb(t_sphere *sphere)
{
	t_aabb	box;
	REAL	r;

	r = sphere->diam * 0.5;
	box.min = fill_point(sphere->center.x - r, sphere->center.y - r, sphere->center.z - r);
	box.max = fill_point(sphere->center.x + r, sphere->center.y + r, sphere->center.z + r);
	return (box);
}
