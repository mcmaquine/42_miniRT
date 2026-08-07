/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 01:16:07 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_material	*get_material_bonus(t_scene_obj *obj)
{
	if (obj->base == SPHERE)
		return (&((t_sphere *)obj)->material);
	if (obj->base == PLANE)
		return (&((t_plane *)obj)->material);
	if (obj->base == CYLINDER)
		return (&((t_cylinder *)obj)->material);
	if (obj->base == CONE)
		return (&((t_cone *)obj)->material);
	return (NULL);
}

static t_point	plane_point(t_hit *hit)
{
	t_plane	*plane;
	t_point	tangent;
	t_point	bitangent;
	t_point	delta;

	plane = (t_plane *)hit->obj;
	if (fabs(plane->normal.y) < 0.999)
		tangent = vec_normalize(vec_cross(fill_point(0, 1, 0),
					plane->normal));
	else
		tangent = fill_point(1, 0, 0);
	bitangent = vec_normalize(vec_cross(plane->normal, tangent));
	delta = vec_sub(hit->point, plane->a_point);
	return (fill_point(vec_dot(delta, tangent),
			vec_dot(delta, bitangent), 0));
}

static t_point	local_point(t_hit *hit)
{
	if (hit->obj->base == SPHERE)
		return (vec_sub(hit->point, ((t_sphere *)hit->obj)->center));
	if (hit->obj->base == PLANE)
		return (plane_point(hit));
	if (hit->obj->base == CYLINDER)
		return (vec_sub(hit->point, ((t_cylinder *)hit->obj)->center));
	if (hit->obj->base == CONE)
		return (vec_sub(hit->point, ((t_cone *)hit->obj)->vertex));
	return (hit->point);
}

void	apply_texture_bonus(t_hit *hit)
{
	t_material	*material;
	t_point		point;
	double		cell;

	if (!hit || !hit->obj)
		return ;
	material = get_material_bonus(hit->obj);
	if (!material || material->pattern != PATTERN_CHECKER)
		return ;
	point = local_point(hit);
	cell = floor(point.x / material->checker_scale);
	cell += floor(point.y / material->checker_scale);
	cell += floor(point.z / material->checker_scale);
	if (fmod(fabs(cell), 2.0) >= 1.0)
		hit->color = material->checker_color;
}
