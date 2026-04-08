/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:41:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 13:45:45 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	
	REAL	half_width = tan(to_radians(win->scene_obj.cam->fov)/2.0);
	REAL	aspect_ratio = (REAL)win->width / (REAL)win->height;
	REAL	ndc_x = (px + 0.5) / win->width;
	REAL	ndc_y = (py + 0.5) / win->height;
	REAL	screen_x = (2 * ndc_x - 1)*aspect_ratio * half_width;
	REAL	screen_y = (1 - 2.0 * ndc_y) * half_width;
	forward = vec_normalize(win->scene_obj.cam->orient);
	world_up = fill_point(0, 1, 0);
	if (fabs(vec_dot(forward, world_up)) > .9999 )
		world_up = fill_point(0, 0, 1);
	right = vec_normalize(vec_cross(world_up, forward));
	up = vec_normalize(vec_cross(forward, right));
	return (direction(vec_add(forward, vec_add(vec_scale(right, screen_x),\
		vec_scale(up, screen_y))), win->scene_obj.cam->point));
}

/*
Return the least value in which a ray intersect an object.
*/
REAL	all_intersections(t_window *win, int px, int py)
{
	REAL	temp;
	REAL	t;
	t_ray	ray;
	int		i;
	REAL	(*intersections[4])(t_window *, t_ray);

	intersections[0] = intersect_plane;
	intersections[1] = intersect_cylinder;
	intersections[2] = intersect_sphere;
	intersections[3] = NULL;
	ray = generate_ray(win, px, py);
	t = DBL_MAX;
	i = 0;
	while (intersections[i])
	{
		temp = (intersections[i])(win, ray);
		if (temp > 0 && temp < t)
			t = temp;
		i++;
	}
	if (t == DBL_MAX)
		return (-1);
	return (t);
}
