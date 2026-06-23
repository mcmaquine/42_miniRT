/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:11 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/17 20:11:41 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_hit	full_intersection(t_plane *plane, t_ray ray);

t_hit	intersect_plane(t_window *win, t_ray ray)
{
	t_list	*planes;
	t_hit	hit;
	t_hit	temp;

	init_t_hit(&hit, -1);
	init_t_hit(&temp, -1);
	planes = win->scene_obj.objs[PLANE];
	if (!planes)
		return (hit);
	hit.t = DBL_MAX;
	while (planes != NULL)
	{
		temp = full_intersection((t_plane *)planes->content, ray);
		if (temp.t > 0 && temp.t < hit.t)
			hit = temp;
		planes = planes->next;
	}
	if (hit.t == DBL_MAX)
		hit.t = -1;
	return (hit);
}

static	t_hit	full_intersection(t_plane *plane, t_ray ray)
{
	REAL	dot;
	t_hit	hit;

	init_t_hit(&hit, -1);
	if (!plane)
		return (hit);
	dot = vec_dot(plane->normal, ray.direction);
	if (!ft_dcmp(dot, 0.0, 1e-2))
		return (hit);
	hit.t = -vec_dot(plane->normal, vec_sub(ray.origin, plane->a_point)) / dot;
	if (hit.t > 0)
	{
		hit.obj = (t_scene_obj *)plane;
		hit.color = plane->color;
	}
	else
		hit.t = -1;
	return (hit);
}
