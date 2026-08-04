/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:41:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:40:09 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_ray	direction(t_point to_normalize, t_point origin);
static t_point	camera_right(t_point forward);
static double	screen_coordinate(int pixel, int size);

t_hit	all_intersections(t_window *win, t_ray ray)
{
	t_hit	temp;
	t_hit	hit;

	init_t_hit(&hit, DBL_MAX);
	temp = intersect_sphere(win, ray);
	if (temp.t > 0 && temp.t < hit.t)
		hit = temp;
	temp = intersect_plane(win, ray);
	if (temp.t > 0 && temp.t < hit.t)
		hit = temp;
	temp = intersect_cylinder(win, ray);
	if (temp.t > 0 && temp.t < hit.t)
		hit = temp;
	temp = intersect_cone(win, ray);
	if (temp.t > 0 && temp.t < hit.t)
		hit = temp;
	if (hit.t == DBL_MAX)
		init_t_hit(&hit, -1);
	if (hit.t > 0)
		calculate_normal(&hit, ray);
	return (hit);
}

t_ray	generate_ray(t_window *win, int px, int py)
{
	t_point	forward;
	t_point	right;
	t_point	up;
	double	half_width;
	double	screen_x;

	half_width = tan(win->scene_obj->cam->fov * 0.5);
	forward = win->scene_obj->cam->orient;
	right = camera_right(forward);
	up = vec_normalize(vec_cross(forward, right));
	screen_x = (2.0 * screen_coordinate(px, win->width) - 1.0)
		* ((double)win->width / (double)win->height) * half_width;
	right = vec_scale(right, screen_x);
	up = vec_scale(up, (1.0 - 2.0 * screen_coordinate(py, win->height))
			* half_width);
	forward = vec_add(forward, vec_add(right, up));
	return (direction(forward, win->scene_obj->cam->point));
}

static t_ray	direction(t_point to_normalize, t_point origin)
{
	t_ray	ray;

	ray.direction = vec_normalize(to_normalize);
	ray.origin = origin;
	return (ray);
}

static t_point	camera_right(t_point forward)
{
	t_point	world_up;

	world_up = fill_point(0, 1, 0);
	if (fabs(vec_dot(forward, world_up)) > 0.9999)
		world_up = fill_point(0, 0, 1);
	return (vec_normalize(vec_cross(world_up, forward)));
}

static double	screen_coordinate(int pixel, int size)
{
	return (((double)pixel + 0.5) / (double)size);
}
