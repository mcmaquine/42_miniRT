#include "minirt_bonus.h"

t_hit	hit_bvh(t_bvh_node *node, t_ray ray)
{
	t_hit	hit;
	t_hit	hit_l;
	t_hit	hit_r;

	init_t_hit(&hit, -1);
	if (!node)
		return (hit);
	if (!hit_box(ray, node->box))
		return (hit);
	hit.t = DBL_MAX;
	if (node->type.base == OBJ)
	{
		if (node->obj->base == SPHERE)
			hit = full_intersection_sphere((t_sphere *)node->obj, ray);
		if (node->obj->base == CYLINDER)
			hit = full_intersection_cylinder((t_cylinder *)node->obj, ray);
		if (hit.t > 0 && hit.t < DBL_MAX)
			return (hit);
		else
			hit.t = -1;
		return (hit);
	}
	else
	{
		hit_l = hit_bvh(node->left, ray);
		hit_r = hit_bvh(node->right, ray);
		if (hit_l.t < 0 && hit_r.t < 0)
		{
			hit.t = -1;
			return (hit);
		}
		if (hit_l.t > 0 && hit_r.t > 0)
		{
			if (hit_l.t < hit_r.t)
				return (hit_l);
			return (hit_r);
		}
		if (hit_l.t < 0 && hit_r.t > 0)
			return (hit_r);
		return (hit_l);
	}
}
