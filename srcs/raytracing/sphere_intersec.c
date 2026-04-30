/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:45:48 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/29 14:26:34 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	REAL	full_intersection(t_sphere *sph, t_ray ray);

/*
This function return a array of spheres. It will be modified when the struct
t_scene change.
*/
t_sphere **find_spheres(t_window *win)
{
	int			count;
	t_list		*objs;
	t_sphere	**sph;

	count = 0;
	objs = win->scene_obj.objs;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == SPHERE)
			count++;
		objs = objs->next;
	}
	sph = ft_calloc(count + 1, sizeof(t_sphere *));
	if (!sph)
		return (NULL);
	objs = win->scene_obj.objs;
	count = 0;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == SPHERE)
			sph[count++] = (t_sphere *)(objs->content);
		objs = objs->next;
	}
	return (sph);
}

REAL	intersect_sphere(t_window *win, t_ray ray)
{
	t_sphere	**sph;
	REAL		t;
	REAL		temp;
	int			i;

	sph = find_spheres(win);
	if (!sph)
		return (-1.0);
	i = -1;
	temp = 0.0;
	t = DBL_MAX;
	while (sph[++i] != NULL)
	{
		temp = full_intersection(sph[i], ray);
		if (temp >= 0 && temp < t)
			t = temp;
	}
	free(sph);
	if (t > 0)
		return (t);
	return (-1);
}

static	REAL	full_intersection(t_sphere *sphere, t_ray ray)
{
	t_point	v_sub;
	REAL	b;
	REAL	delta;
	REAL	t;

	if (!sphere)
		return (-1);
	v_sub = vec_sub(ray.origin, sphere->center);
	b = 2 * vec_dot(ray.direction, v_sub);
	delta = b * b - 4 * (vec_dot(v_sub, v_sub)\
		- sphere->diam*0.5 * sphere->diam*0.5);
	t = roots (1, 2 * vec_dot(ray.direction, v_sub), vec_dot(v_sub, v_sub)\
	- sphere->diam * sphere->diam * 0.25);
	return (t);
}
