/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 14:30:54 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/25 18:48:38 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_aabb	cylinder_aabb(t_cylinder *cylinder)
{
	t_aabb	box;
	t_point	center_base;
	t_point	center_top;
	//t_point	min;
	//t_point max;
	REAL	r;

	center_base = cylinder->base.a_point;
	center_top = cylinder->top.a_point;
	r = cylinder->diam * 0.5;
	box.min.x = real_min(center_base.x - r, center_top.x - r);
	box.min.y = real_min(center_base.y - r, center_top.y - r);
	box.min.z = real_min(center_base.z - r, center_top.z - r);
	box.max.x = real_max(center_base.x + r, center_top.x + r);
	box.max.y = real_max(center_base.y + r, center_top.y + r);
	box.max.z = real_max(center_base.z + r, center_top.z + r);
	//box.min = min;
	//box.max = max;
	return (box);
}
