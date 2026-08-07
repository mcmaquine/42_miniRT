/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 22:48:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 01:10:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Free all memory allocated for t_scene_obj
*/
void	free_scene_obj(t_scene **scene_obj)
{
	int	i;

	if (!(*scene_obj))
		return ;
	free((*scene_obj)->amb);
	free((*scene_obj)->cam);
	free((*scene_obj)->light);
	i = -1;
	while (++i < COUNT)
		ft_lstclear(&((*scene_obj)->objs)[i], free);
	free(*scene_obj);
	*scene_obj = NULL;
}

/*
Fill point struct and validate if every coordinate is in range [min,max]
*/
int	fill_coordinate(char *param, t_point *point, t_objs_type obj)
{
	char	**points;

	points = ft_split(param, ',');
	if (ft_sizeof_split(points) != 3)
	{
		print_error(obj, ERR_NO_PARAM_COORDS, 0);
		ft_free_split(points);
		return (1);
	}
	if (!is_valid_number(points[0]) || !is_valid_number(points[1])
		|| !is_valid_number(points[2]))
	{
		print_error(obj, ERR_COORDS_INVALID, 0);
		ft_free_split(points);
		return (1);
	}
	point->x = ft_atod(points[0]);
	point->y = ft_atod(points[1]);
	point->z = ft_atod(points[2]);
	ft_free_split(points);
	return (0);
}
