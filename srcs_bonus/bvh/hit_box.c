/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 15:26:26 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/12 17:48:11 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	slab_test(t_point *min, t_point *max, t_ray ray, t_aabb box);
static void	swap_real(REAL *a, REAL *b);

int	hit_box(t_ray ray, t_aabb box)
{
	t_point axis_min;
	t_point axis_max;
	REAL	entry;
	REAL	exit;

	slab_test(&axis_min, &axis_max, ray, box);
	entry = real_max(axis_min.x, axis_min.y, axis_min.z);
	exit = real_min(axis_max.x, axis_max.y, axis_max.z);
	if (exit < 0 || entry > exit)
		return (0);
	return (1);
}

static void	slab_test(t_point *min, t_point *max, t_ray ray, t_aabb box)
{
	min->x = (box.min.x - ray.origin.x) / ray.direction.x;
	max->x = (box.max.x - ray.origin.x) / ray.direction.x;
	if (min->x > max->x)
		swap_real(&min->x, &max->x);
	min->y = (box.min.y - ray.origin.y) / ray.direction.y;
	max->y = (box.max.y - ray.origin.y) / ray.direction.y;
	if (min->y > max->y)
		swap_real(&min->y, &max->y);
	min->z = (box.min.z - ray.origin.z) / ray.direction.z;
	max->z = (box.max.z - ray.origin.z) / ray.direction.z;
	if (min->z > max->z)
		swap_real(&min->z, &max->z);
}

static void	swap_real(REAL *a, REAL *b)
{
	REAL temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
