/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:10:05 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:38:38 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	sphere_normal(t_hit *hit);
static void	cylinder_normal(t_hit *hit);
static void	cone_normal(t_hit *hit);

/*
Compute normal vector to a point P on t
*/
void	calculate_normal(t_hit *hit, t_ray ray)
{
	if (!hit->obj)
		return ;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, hit->t));
	if (hit->obj->base == SPHERE)
		sphere_normal(hit);
	else if (hit->obj->base == PLANE)
		hit->normal = ((t_plane *)hit->obj)->normal;
	else if (hit->obj->base == CYLINDER)
		cylinder_normal(hit);
	else if (hit->obj->base == CONE)
		cone_normal(hit);
}

static void	sphere_normal(t_hit *hit)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)hit->obj;
	hit->normal = vec_normalize(vec_sub(hit->point, sphere->center));
}

static void	cylinder_normal(t_hit *hit)
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

static void	cone_normal(t_hit *hit)
{
	t_point	p;
	t_point	v;
	t_cone	*cone;
	REAL	h;

	if (!hit->obj)
		return ;
	cone = (t_cone *)hit->obj;
	p = vec_sub(hit->point, cone->vertex);
	h = vec_dot(p, cone->v_axis);
	v = vec_scale(cone->v_axis, h * (1.0 + cone->tan2));
	hit->normal = vec_normalize(vec_sub(p, v));
}
