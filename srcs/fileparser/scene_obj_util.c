/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:24:04 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 11:24:17 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Free all memory allocated for t_scene_obj
*/
void	free_scene_obj(t_scene **scene_obj)
{
	if (!(*scene_obj))
		return ;
	free((*scene_obj)->amb);
	free((*scene_obj)->cam);
	free((*scene_obj)->light);
	ft_lstclear(&((*scene_obj)->objs), free);
	free(*scene_obj);
	*scene_obj = NULL;
}

/*
Fill struct point and checks its params.
*/
int	fill_color(char *param, t_color *color)
{
	char	**colors;

	colors = ft_split(param, ',');
	if (ft_sizeof_split(colors) != 3)
	{
		ft_free_split(colors);
		return (1);
	}
	color->red = ft_atoi(colors[0]);
	color->green = ft_atoi(colors[1]);
	color->blue = ft_atoi(colors[2]);
	color->tpcy = 0;
	ft_free_split(colors);
	if ((color->red < 0 || color->red > 255) 
		|| (color->green < 0 || color->green > 255)
		|| (color->blue < 0 || color->blue > 255))
		return (1);
	return (0);
}

/*
Fill point struct and validate if every coordinate is in range [min,max]
*/
int	fill_coordinate(char *param, t_point *point, REAL min, REAL max)
{
	char	**points;

	points = ft_split(param, ',');
	if (ft_sizeof_split(points) != 3)
	{
		ft_free_split(points);
		return (1);
	}
	point->x = ft_atod(points[0]);
	point->y = ft_atod(points[1]);
	point->z = ft_atod(points[2]);
	ft_free_split(points);
	if (min == 0.0 && max == 0.0)
		return (0);
	else if ((point->x < min || point->x > max)
		|| (point->y < min || point->y > max)
		|| (point->z < min || point->z > max))
		return (1);
	return (0);
}
