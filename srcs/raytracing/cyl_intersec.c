/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_intersec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:41:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/30 16:13:48 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_hit	full_intersection(t_cylinder *sph, t_ray ray);
static	t_hit	check_height_intersec(t_cylinder *cyl, t_ray r, REAL t);
static	t_hit	check_face_intersec(t_plane *p, REAL r_sq, t_ray r);
static	t_hit	check_tube_intersec(t_cylinder *cyl, t_ray ray ,t_point co);

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
	hit_top = check_face_intersec(&(cyl->top), cyl->radius, ray);
	hit_base = check_face_intersec(&(cyl->base), cyl->radius, ray);
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
	t_hit	hit;

	init_t_hit(&hit, -1);
	if (!cyl)
		return (hit);
	hit.t = DBL_MAX;
	dv_axis = vec_dot(ray.direction, cyl->v_axis);
	cov_axis = vec_dot(co, cyl->v_axis);
	dco = vec_dot(co, ray.direction);
	co_sq = vec_magnitude(co);
	co_sq = co_sq * co_sq;
	hit.t = roots(1.0 - dv_axis*dv_axis, 2*(dco - dv_axis*cov_axis),\
	co_sq - cov_axis*cov_axis - cyl->r_sq);
	if (hit.t > 0)
	{
		hit.obj = (t_scene_obj *)cyl;
		hit.color = cyl->color;
	}
	hit = check_height_intersec(cyl, ray, hit.t);
	return (hit);
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

static t_hit	check_face_intersec(t_plane *p, REAL radius, t_ray r)
{
	t_point	pt;
	t_hit	hit;
	REAL	dot;
	REAL	dist;

	init_t_hit(&hit, -1);
	if (!p)
		return (hit);
	dot = vec_dot(p->normal, r.direction);
	if (!ft_dcmp(dot, 0.0, 1e-5))
		return (hit);
	hit.t = -vec_dot(p->normal, vec_sub(r.origin, p->a_point)) / dot;
	if (hit.t > 0)
	{
		pt = vec_add(r.origin , vec_scale(r.direction, hit.t));
		dist = vec_magnitude(vec_sub(pt, p->a_point));
		if (dist <= radius)
		{
			hit.obj = (t_scene_obj *)p;
			hit.color = p->color;
		}
		else
			hit.t = -1;
	}
	return (hit);
}
