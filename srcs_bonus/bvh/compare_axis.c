#include "minirt_bonus.h"

int	compare_x(const void *a, const void *b)
{
	t_scene_obj	*obj_a;
	t_scene_obj	*obj_b;
	t_aabb		box_a;
	t_aabb		box_b;

	obj_a = *(t_scene_obj **)a;
	obj_b = *(t_scene_obj **)b;
	box_a = get_aabb(obj_a);
	box_b = get_aabb(obj_b);
	if ((box_a.max.x + box_a.min.x) * 0.5 > (box_b.max.x + box_b.min.x) * 0.5)
		return (1);
	if ((box_a.max.x + box_a.min.x) * 0.5 < (box_b.max.x + box_b.min.x) * 0.5)
		return (-1);
	return (0);
}

int	compare_y(const void *a, const void *b)
{
	t_scene_obj	*obj_a;
	t_scene_obj	*obj_b;
	t_aabb		box_a;
	t_aabb		box_b;

	obj_a = *(t_scene_obj **)a;
	obj_b = *(t_scene_obj **)b;
	box_a = get_aabb(obj_a);
	box_b = get_aabb(obj_b);
	if ((box_a.max.y + box_a.min.y) * 0.5 > (box_b.max.y + box_b.min.y) * 0.5)
		return (1);
	if ((box_a.max.y + box_a.min.y) * 0.5 < (box_b.max.y + box_b.min.y) * 0.5)
		return (-1);
	return (0);
}

int	compare_z(const void *a, const void *b)
{
	t_scene_obj	*obj_a;
	t_scene_obj	*obj_b;
	t_aabb		box_a;
	t_aabb		box_b;

	obj_a = *(t_scene_obj **)a;
	obj_b = *(t_scene_obj **)b;
	box_a = get_aabb(obj_a);
	box_b = get_aabb(obj_b);
	if ((box_a.max.z + box_a.min.z) * 0.5 > (box_b.max.z + box_b.min.z) * 0.5)
		return (1);
	if ((box_a.max.z + box_a.min.z) * 0.5 < (box_b.max.z + box_b.min.z) * 0.5)
		return (-1);
	return (0);
}
