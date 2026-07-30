/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 18:49:56 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/25 19:03:50 by gabrgarc         ###   ########.fr       */
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
	return (box);
}
