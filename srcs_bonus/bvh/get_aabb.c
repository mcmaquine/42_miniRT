/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 18:49:56 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/05 21:14:52 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_aabb	get_aabb(t_scene_obj *obj)
{
	t_aabb	box;

	box = (t_aabb){0};
	if (obj->base == SPHERE)
		box = sphere_aabb((t_sphere *)obj);
	if (obj->base == CYLINDER)
		box = cylinder_aabb((t_cylinder *)obj);
	if (obj->base == CONE)
		box = cone_aabb((t_cone *)obj);
	return (box);
}
