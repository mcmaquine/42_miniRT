/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bvh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 23:48:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 00:00:03 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_hit	hit_bvh_leaf(t_bvh_node *node, t_ray ray);
static t_hit	pick_closest_hit(t_hit hit_l, t_hit hit_r);

t_hit	hit_bvh(t_bvh_node *node, t_ray ray)
{
	t_hit	hit;
	t_hit	hit_l;
	t_hit	hit_r;

	init_t_hit(&hit, -1);
	if (!node)
		return (hit);
	if (!hit_box(ray, node->box))
		return (hit);
	if (node->type.base == OBJ)
		return (hit_bvh_leaf(node, ray));
	hit_l = hit_bvh(node->left, ray);
	hit_r = hit_bvh(node->right, ray);
	return (pick_closest_hit(hit_l, hit_r));
}

static t_hit	hit_bvh_leaf(t_bvh_node *node, t_ray ray)
{
	t_hit	hit;

	init_t_hit(&hit, -1);
	if (node->obj->base == SPHERE)
		hit = full_intersection_sphere((t_sphere *)node->obj, ray);
	if (node->obj->base == CYLINDER)
		hit = full_intersection_cylinder((t_cylinder *)node->obj, ray);
	if (node->obj->base == CONE)
		hit = full_intersection_cone((t_cone *)node->obj, ray);
	if (hit.t > 0 && hit.t < DBL_MAX)
		return (hit);
	hit.t = -1;
	return (hit);
}

static t_hit	pick_closest_hit(t_hit hit_l, t_hit hit_r)
{
	t_hit	hit;

	init_t_hit(&hit, -1);
	if (hit_l.t < 0 && hit_r.t < 0)
		return (hit);
	if (hit_l.t > 0 && hit_r.t > 0)
	{
		if (hit_l.t < hit_r.t)
			return (hit_l);
		return (hit_r);
	}
	if (hit_l.t < 0 && hit_r.t > 0)
		return (hit_r);
	return (hit_l);
}
