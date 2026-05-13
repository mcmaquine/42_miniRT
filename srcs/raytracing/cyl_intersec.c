/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_intersec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:41:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/05/13 19:50:06 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	REAL	full_intersection(t_cylinder *sph, t_ray ray);
static	REAL	check_height_intersec(t_cylinder *cyl, t_ray r, REAL t);
static	REAL	check_face_intersec(t_plane *p, REAL r_sq, t_ray r);
static	REAL	check_tube_intersec(t_cylinder *cyl, t_ray ray);

REAL	intersect_cylinder(t_window *win, t_ray ray)
{
	t_list	*cyl;
	REAL	t;
	REAL	temp;
	int		i;

	cyl = win->scene_obj.objs[CYLINDER];
	if (!cyl)
		return (-1.0);
	i = -1;
	temp = 0.0;
	t = DBL_MAX;
	while (cyl != NULL)
	{
		temp = full_intersection((t_cylinder *)cyl->content, ray);
		if (temp >= 0 && temp < t)
			t = temp;
		cyl = cyl->next;
	}
	if (t > 0)
		return (t);
	return (-1);
}

static	REAL	full_intersection(t_cylinder *cyl, t_ray ray)
{
	REAL	t_top;
	REAL	t_base;
	REAL	t_tube;
	REAL	t_small;

	t_top = check_face_intersec(&(cyl->top), cyl->diam*.5, ray);
	t_base = check_face_intersec(&(cyl->base), cyl->r_sq, ray);
	t_tube = check_tube_intersec(cyl, ray);
	t_small = DBL_MAX;
	if (t_base < t_small && t_base > 0)
		t_small = t_base;
	if (t_small == -1 || (t_tube < t_small && t_tube > 0))
		t_small = t_tube;
	return (t_small);
}

static REAL	check_tube_intersec(t_cylinder *cyl, t_ray ray)
{
	REAL	dv_axis;
	REAL	cov_axis;
	REAL	co_sq;
	REAL	dco;
	REAL	t;

	t = DBL_MAX;
	if (!cyl)
		return (-1);
	dv_axis = vec_dot(ray.direction, cyl->v_axis);
	cov_axis = vec_dot(vec_sub(ray.origin, cyl->center), cyl->v_axis);
	dco = vec_dot(vec_sub(ray.origin, cyl->center), ray.direction);
	co_sq = vec_magnitude(vec_sub(ray.origin, cyl->center));
	co_sq = co_sq * co_sq;
	t = roots(1.0 - dv_axis*dv_axis, 2*(dco - dv_axis*cov_axis),\
	co_sq - cov_axis*cov_axis - cyl->r_sq);
	t = check_height_intersec(cyl, ray, t);
	return (t);
}

static	REAL	check_height_intersec(t_cylinder *cyl, t_ray r, REAL t)
{
	t_point	point;
	REAL	h;

	if (t < 0)
		return (t);
	point = vec_add(r.origin, vec_scale(r.direction, t));
	h = vec_dot(vec_sub(point, cyl->center), cyl->v_axis);
	if (h > cyl->height_2 || h < -cyl->height_2)
		return (-1);
	else
		return (t);
}

static REAL	check_face_intersec(t_plane *p, REAL rad, t_ray r)
{
	REAL	dot;
	REAL	t;
	t_point	pt;
	REAL	dist;

	if (!p)
		return (-1);
	t = -1;
	dot = vec_dot(p->normal, r.direction);
	if (!ft_dcmp(dot, 0.0, 1e-5))
		return (-1);
	t = -vec_dot(p->normal, vec_sub(r.origin, p->a_point)) / dot;
	if (t > 0)
	{
		pt = vec_add(r.origin , vec_scale(r.direction, t));
		dist = vec_magnitude(vec_sub(pt, p->a_point));
		if (dist <= rad)
			return (t);
		else
			return (-1);
	}
	else
		return (t);
}
