/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:10:05 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 13:47:43 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void cylinder_normal(t_hit *hit);

/*
Compute normal vector to a point P on t
*/
void	calculate_normal(t_hit *hit, t_ray ray)
{
	if (!hit->obj)
		return ;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, hit->t));
	if (hit->obj->base == SPHERE)
		hit->normal = vec_normalize(vec_sub(hit->point,\
			((t_sphere *)hit->obj)->center));
	else if (hit->obj->base == PLANE)
		hit->normal = ((t_plane *)hit->obj)->normal;
	else if (hit->obj->base == CYLINDER)
		cylinder_normal(hit);
}

static void cylinder_normal(t_hit *hit)
{
	t_point		p;
	t_point		v;
	t_cylinder	*cyl;

	if (!hit->obj)
		return ;
	cyl = (t_cylinder *)hit->obj;
	p = vec_sub(hit->point, cyl->center);
	v = vec_scale(cyl->v_axis, vec_dot(p, cyl->v_axis));
	hit->normal = vec_normalize(vec_sub(p, v));
}
