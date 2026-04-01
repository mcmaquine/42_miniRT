/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:41:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/01 18:37:36 by mmaquine         ###   ########.fr       */
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
	
	double	half_width = tan(to_radians(win->scene_obj.cam->fov)/2.0);
	double	aspect_ratio = (double)win->width / (double)win->height;
	double	ndc_x = (px + 0.5) / win->width;
	double	ndc_y = (py + 0.5) / win->height;
	double	screen_x = (2 * ndc_x - 1)*aspect_ratio * half_width;
	double	screen_y = (1 - 2.0 * ndc_y) * half_width;
	forward = vec_normalize(win->scene_obj.cam->orient);
	world_up = fill_point(0, 1, 0);
	if (fabs(vec_dot(forward, world_up)) > .9999 )
		world_up = fill_point(0, 0, 1);
	right = vec_normalize(vec_cross(world_up, forward));
	up = vec_normalize(vec_cross(forward, right));
	return (direction(vec_add(forward, vec_add(vec_scale(right, screen_x),\
		vec_scale(up, screen_y))), win->scene_obj.cam->point));
}

double	intersect_plane(t_window *win, t_ray ray)
{
	t_plane	*planes;
	double	t;
	double	temp;
	int		i;

	//return a NULL terminated array of planes
	planes = find_planes(win);
	if (!planes)
		return (-1.0);
	i = 0;
	temp = 0.0;
	while (planes[i])
	{
		if (!ft_dcmp(vec_dot(planes[i]->normal, ray.direction), 0.0, 1e-5))
			return (-1);
		t = -vec_dot(planes[i]->normal, vec_sub(ray.origin, planes[i]->a_point))\
			/vec_dot(planes[i]->normal, ray.direction);	
	}
	if (t > 0)
		return (t);
	else
		return (-1);
}
