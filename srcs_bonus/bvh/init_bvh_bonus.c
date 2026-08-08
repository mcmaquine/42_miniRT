/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 21:05:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/31 21:19:34 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_bvh(t_scene *scene)
{
	int			n;
	t_scene_obj	**array;

	n = count_objs(scene->objs);
	if (n == 0)
		return ;
	array = array_objs(scene->objs, n);
	if (!array)
		return ;
	scene->tree = build_bvh(array, n);
	free(array);
}
