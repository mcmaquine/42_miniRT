/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:45:48 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 13:47:45 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_hit	full_intersection_sphere(t_sphere *sph, t_ray ray);

t_hit	intersect_sphere(t_window *win, t_ray ray)
{
	t_list	*sph;
	t_hit	temp;
	t_hit	hit;

	init_t_hit(&hit, -1);
	sph = win->scene_obj->objs[SPHERE];
	if (!sph)
		return (hit);
	hit.t = DBL_MAX;
	while (sph != NULL)
	{
		temp = full_intersection_sphere((t_sphere *)sph->content, ray);
		if (temp.t >= 0 && temp.t < hit.t)
			hit = temp;
		sph = sph->next;
	}
	if (hit.t > 0 && hit.t < DBL_MAX)
		return (hit);
	else
		hit.t = -1;
	return (hit);
}

t_hit	full_intersection_sphere(t_sphere *sphere, t_ray ray)
{
	t_point	v_sub;
	double	b;
	t_hit	hit;

	init_t_hit(&hit, -1);
	if (!sphere)
		return (hit);
	v_sub = vec_sub(ray.origin, sphere->center);
	b = 2 * vec_dot(ray.direction, v_sub);
	hit.t = roots (1, b, vec_dot(v_sub, v_sub) - sphere->r_sq);
	if (hit.t > 0)
	{
		hit.obj = (t_scene_obj *)sphere;
		hit.color = sphere->color;
	}
	else
		hit.t = -1;
	return (hit);
}
