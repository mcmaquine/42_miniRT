/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_intersec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:41:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/31 15:53:45 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static	t_hit	full_intersection(t_cylinder *sph, t_ray ray);
static	t_hit	check_height_intersec(t_cylinder *cyl, t_ray r, REAL t);
static	t_hit	check_tube_intersec(t_cylinder *cyl, t_ray ray, t_point co);

t_hit	intersect_cylinder(t_window *win, t_ray ray)
{
	t_list	*cyl;
	t_hit	hit;
	t_hit	temp;

	init_t_hit(&hit, -1);
	cyl = win->scene_obj->objs[CYLINDER];
	if (!cyl)
		return (hit);
	hit.t = DBL_MAX;
	while (cyl != NULL)
	{
		temp = full_intersection((t_cylinder *)cyl->content, ray);
		if (temp.t >= 0 && temp.t < hit.t)
			hit = temp;
		cyl = cyl->next;
	}
	return (hit);
}

static	t_hit	full_intersection(t_cylinder *cyl, t_ray ray)
{
	t_hit	hit_top;
	t_hit	hit_base;
	t_hit	hit_tube;
	t_hit	hit_small;

	init_t_hit(&hit_small, DBL_MAX);
	hit_top = circular_plane_intersec(&(cyl->top), cyl->radius, ray);
	hit_base = circular_plane_intersec(&(cyl->base), cyl->radius, ray);
	hit_tube = check_tube_intersec(cyl, ray, vec_sub(ray.origin, cyl->center));
	if (hit_base.t < hit_small.t && hit_base.t > 0)
		hit_small = hit_base;
	if (hit_top.t < hit_small.t && hit_top.t > 0)
		hit_small = hit_top;
	if (hit_tube.t < hit_small.t && hit_tube.t > 0)
		hit_small = hit_tube;
	if (hit_small.t == DBL_MAX)
		hit_small.t = -1;
	return (hit_small);
}

static t_hit	check_tube_intersec(t_cylinder *cyl, t_ray ray, t_point co)
{
	REAL	dv_axis;
	REAL	cov_axis;
	REAL	co_sq;
	REAL	dco;

	if (!cyl)
		return (check_height_intersec(cyl, ray, -1));
	dv_axis = vec_dot(ray.direction, cyl->v_axis);
	cov_axis = vec_dot(co, cyl->v_axis);
	dco = vec_dot(co, ray.direction);
	co_sq = vec_magnitude(co);
	co_sq = co_sq * co_sq;
	return (check_height_intersec(cyl, ray,
			roots(1.0 - dv_axis * dv_axis,
				2 * (dco - dv_axis * cov_axis),
				co_sq - cov_axis * cov_axis - cyl->r_sq)));
}

/*
Checks if tubes intersection goes beyond cylinder height
*/
static	t_hit	check_height_intersec(t_cylinder *cyl, t_ray r, REAL t)
{
	t_point	point;
	t_hit	hit;
	REAL	h;

	init_t_hit(&hit, -1);
	if (t < 0)
		return (hit);
	point = vec_add(r.origin, vec_scale(r.direction, t));
	h = vec_dot(vec_sub(point, cyl->center), cyl->v_axis);
	if (h > cyl->height_2 || h < -cyl->height_2)
		hit.t = -1;
	else
	{
		hit.t = t;
		hit.obj = (t_scene_obj *)cyl;
		hit.color = cyl->color;
	}
	return (hit);
}
