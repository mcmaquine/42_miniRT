/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:11 by mmaquine          #+#    #+#             */
/*   Updated: 2026/05/12 15:13:55 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	REAL	full_intersection(t_plane *plane, t_ray ray);

/*
This function return a array of planes. It will be modified when the struct
t_scene change.
*/
/*
t_plane	**find_planes(t_window *win)
{
	int			count;
	t_list		*objs;
	t_plane		**planes;

	count = 0;
	objs = win->scene_obj.objs;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == PLANE)
			count++;
		objs = objs->next;
	}
	planes = ft_calloc(count + 1, sizeof(t_plane *));
	if (!planes)
		return (NULL);
	objs = win->scene_obj.objs;
	count = 0;
	while (objs)
	{
		if (((t_scene_obj *)(objs->content))->type == PLANE)
			planes[count++] = (t_plane *)(objs->content);	
		objs = objs->next;
	}
	return (planes);
}
*/

REAL	intersect_plane(t_window *win, t_ray ray)
{
	t_list	*planes;
	REAL	t;
	REAL	temp;
	int		i;

	planes = win->scene_obj.objs[PLANE];
	if (!planes)
		return (-1.0);
	i = -1;
	temp = 0.0;
	t = DBL_MAX;
	while (planes != NULL)
	{
		temp = full_intersection((t_plane *)planes->content, ray);
		if (temp >= 0 && temp < t)
			t = temp;
		planes = planes->next;
	}
	if (t > 0)
		return (t);
	return (-1);
}

static	REAL	full_intersection(t_plane *plane, t_ray ray)
{
	REAL	dot;

	if (!plane)
		return (-1);
	dot = vec_dot(plane->normal, ray.direction);
	if (!ft_dcmp(dot, 0.0, 1e-5))
		return (-1);
	return (-vec_dot(plane->normal, vec_sub(ray.origin, plane->a_point))\
			/dot);
}
