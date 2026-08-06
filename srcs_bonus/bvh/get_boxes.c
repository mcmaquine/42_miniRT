/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_boxes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 20:30:16 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/05 20:59:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_aabb	sphere_aabb(t_sphere *sph)
{
	t_aabb	box;
	double	r;

	r = sphere->diam * 0.5;
	box.min = fill_point(sphere->center.x - r, sphere->center.y - r, sphere->center.z - r);
	box.max = fill_point(sphere->center.x + r, sphere->center.y + r, sphere->center.z + r);
	return (box);
}

t_aabb	cylinder_aabb(t_cylinder *cylinder)
{
	t_aabb	box;
	t_point	center_base;
	t_point	center_top;
	double	r;

	center_base = cylinder->base.a_point;
	center_top = cylinder->top.a_point;
	r = cylinder->diam * 0.5;
	box.min.x = real_min(center_base.x - r, center_top.x - r, center_top.x - r);
	box.min.y = real_min(center_base.y - r, center_top.y - r, center_top.y - r);
	box.min.z = real_min(center_base.z - r, center_top.z - r, center_top.z - r);
	box.max.x = real_max(center_base.x + r, center_top.x + r, center_top.x + r);
	box.max.y = real_max(center_base.y + r, center_top.y + r, center_top.y + r);
	box.max.z = real_max(center_base.z + r, center_top.z + r, center_top.z + r);
	return (box);
}

t_aabb	cone_aabb(t_cone *cone)
{
	t_aabb	box;
	t_point	base;
	t_point 
	double	r;

	base = cone->base.a_point;
	r = cone->radius;
	box.min.x = real_min(base.x - r, cone->vertex.x, cone->vertex.x);
	box.min.y = real_min(base.y - r, cone->vertex.y, cone->vertex.y);
	box.min.z = real_min(base.z - r, cone->vertex.z, cone->vertex.z);
	box.max.x = real_max(base.x + r, cone->vertex.x, cone->vertex.x);
	box.max.y = real_max(base.y + r, cone->vertex.y, cone->vertex.y);
	box.max.z = real_max(base.z + r, cone->vertex.z, cone->vertex.z);
	return (box);
}
