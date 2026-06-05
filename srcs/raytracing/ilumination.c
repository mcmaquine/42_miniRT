#include "minirt.h"

static void cylinder_normal(t_hit *hit, t_ray ray)
{
	t_point		p;
	t_point		v;

	p = vec_sub(hit->point, cyl->center);
	v = vec_scale(cyl->v_axis, vec_dot(p, cyl->v_axis));
	hit->normal = vec_normalize(vec_sub(p, v));
}

t_color	calculate_illumination(t_window *win, t_hit hit)
{
	t_color	color;
	t_list	*lights;

	init_t_color(&color, 0, 0, 0);
	lights = win->scene_obj.objs[LIGHT];
	while (lights != NULL)
	{
		color = add_color(color, calculate_light(win, hit, (t_light *)lights->content));
		lights = lights->next;
	}
	return (color);
}

void	calculate_illumination_amb(t_window *win, t_hit *hit)
{
	if (win->scene_obj.amb)
		hit->color = add_color(hit->color, mult_color(win->scene_obj.amb->color, win->scene_obj.amb->bright_rate));
}

void	calculate_normal(t_hit *hit, t_ray ray)
{
	if (!hit->obj)
		return ;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, hit->t));
	if (hit->obj->base == SPHERE)
		hit->normal = vec_normalize(vec_sub(hit->point,\
			((t_sphere *)hit->obj)->center));
	else if (hit->obj->base == PLANE)
		hit->normal = ((t_plane *)hit->obj)->normal;
	else if (hit->obj->base == CYLINDER)
	{
		t_cylinder	*cyl;
		t_point		p;

		cyl = (t_cylinder *)hit->obj;
		p = vec_sub(hit->point, cyl->center);
		hit->normal = vec_normalize(vec_sub(p, vec_scale(cyl->v_axis,\
			vec_dot(p, cyl->v_axis))));
	}
}
