/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:41:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 13:47:46 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_ray	direction(t_point	to_normalize, t_point origin)
{
	t_ray	ray;

	ray.direction = vec_normalize(to_normalize);
	ray.origin = origin;
	return (ray);
}

//tem que normionetear
t_ray	generate_ray(t_window *win, int px, int py)
{
	t_point	forward;
	t_point	world_up;
	t_point	right;
	t_point	up;

	double	half_width = tan(to_radians(win->scene_obj->cam->fov)/2.0);
	double	aspect_ratio = (double)win->width / (double)win->height;
	double	ndc_x = (px + 0.5) / win->width;
	double	ndc_y = (py + 0.5) / win->height;
	double	screen_x = (2 * ndc_x - 1)*aspect_ratio * half_width;
	double	screen_y = (1 - 2.0 * ndc_y) * half_width;
	forward = vec_normalize(win->scene_obj->cam->orient);
	world_up = fill_point(0, 1, 0);
	if (fabs(vec_dot(forward, world_up)) > .9999 )
		world_up = fill_point(0, 0, 1);
	right = vec_normalize(vec_cross(world_up, forward));
	up = vec_normalize(vec_cross(forward, right));
	return (direction(vec_add(forward, vec_add(vec_scale(right, screen_x),\
		vec_scale(up, screen_y))), win->scene_obj->cam->point));
}

/*
Return the least t value and object associated to it in which a ray intersect an
object.
*/
t_hit	all_intersections(t_window *win, t_ray ray)
{
	t_hit	temp;
	t_hit	hit;
	int		i;
	t_hit	(*intersections[4])(t_window *, t_ray);

	intersections[PLANE] = intersect_plane;
	intersections[CYLINDER] = intersect_cylinder;
	intersections[SPHERE] = intersect_sphere;
	intersections[3] = NULL;
	init_t_hit(&hit, DBL_MAX);
	i = -1;
	while (intersections[++i])
	{
		temp = (intersections[i])(win, ray);
		if (temp.t > 0 && temp.t < hit.t)
			hit = temp;
	}
	if (hit.t == DBL_MAX)
		init_t_hit(&hit, -1);
	if (hit.t > 0)
		calculate_normal(&hit, ray);
	return (hit);
}
