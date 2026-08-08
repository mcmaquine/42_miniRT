/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 23:47:37 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 23:47:38 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_aabb	group_aabb(t_scene_obj **objs, int n)
{
	t_aabb	box;
	t_aabb	current_box;
	int		i;

	box = get_aabb(objs[0]);
	i = 1;
	while (i < n)
	{
		current_box = get_aabb(objs[i]);
		box.min.x = real_min(box.min.x, current_box.min.x, current_box.min.x);
		box.min.y = real_min(box.min.y, current_box.min.y, current_box.min.y);
		box.min.z = real_min(box.min.z, current_box.min.z, current_box.min.z);
		box.max.x = real_max(box.max.x, current_box.max.x, current_box.max.x);
		box.max.y = real_max(box.max.y, current_box.max.y, current_box.max.y);
		box.max.z = real_max(box.max.z, current_box.max.z, current_box.max.z);
		i++;
	}
	return (box);
}
