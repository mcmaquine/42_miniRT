/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_intersec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:41:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/29 15:23:14 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	REAL	full_intersection(t_cylinder *sph, t_ray ray);

t_cylinder	**find_cylinders(t_window *win)
{
	int			count;
	t_list		*objs;
	t_cylinder	**cyl;

	count = 0;
	objs = win->scene_obj.objs;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == CYLINDER)
			count++;
		objs = objs->next;
	}
	cyl = ft_calloc(count + 1, sizeof(t_cylinder *));
	if (!cyl)
		return (NULL);
	objs = win->scene_obj.objs;
	count = 0;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == CYLINDER)
			cyl[count++] = (t_cylinder *)(objs->content);
		objs = objs->next;
	}
	return (cyl);
}

REAL	intersect_cylinder(t_window *win, t_ray ray)
{
	t_cylinder	**cyl;
	REAL		t;
	REAL		temp;
	int			i;

	cyl = find_cylinders(win);
	if (!cyl)
		return (-1.0);
	i = -1;
	temp = 0.0;
	t = DBL_MAX;
	while (cyl[++i] != NULL)
	{
		temp = full_intersection(cyl[i], ray);
		if (temp >= 0 && temp < t)
			t = temp;
	}
	free(cyl);
	if (t > 0)
		return (t);
	return (-1);
}

static REAL	full_intersection(t_cylinder *cylinder, t_ray ray)
{
	REAL	dv_axis;
	REAL	cov_axis;
	REAL	co_sq;
	REAL	dco;
	REAL	t;

	t = DBL_MAX;
	if (!cylinder)
		return (-1);
	dv_axis = vec_dot(ray.direction, cylinder->v_axis);
	cov_axis = vec_dot(vec_sub(ray.origin, cylinder->center), cylinder->v_axis);
	dco = vec_dot(vec_sub(ray.origin, cylinder->center), ray.direction);
	co_sq = vec_magnitude(vec_sub(ray.origin, cylinder->center));
	co_sq = co_sq * co_sq;
	t = roots(1.0 - dv_axis*dv_axis, 2*(dco - dv_axis*cov_axis),\
	co_sq - cov_axis*cov_axis - cylinder->diam * cylinder->diam * 0.25);
	return (t);
}

