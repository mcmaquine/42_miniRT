/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:24:04 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/27 17:27:21 by gabrgarc         ###   ########.fr       */
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
Fill struct point and checks its params.
*/
int	fill_color(char *param, t_color *color, t_objs_type obj)
{
	char	**colors;
	t_color	temp;

	colors = ft_split(param, ',');
	if (ft_sizeof_split(colors) != 3)
	{
		print_error(obj, ERR_NO_PARAM_COLOR, 0);
		ft_free_split(colors);
		return (1);
	}
	temp.red = ft_atoi(colors[0]);
	temp.green = ft_atoi(colors[1]);
	temp.blue = ft_atoi(colors[2]);
	color->tpcy = 0.0;
	ft_free_split(colors);
	if ((temp.red < 0 || temp.red > 255) 
		|| (temp.green < 0 || temp.green > 255)
		|| (temp.blue < 0 || temp.blue > 255))
	{
		print_error(obj, ERR_OUT_RANGE_COLOR, 0);
		return (1);
	}
	color->red = temp.red / 255.0;
	color->green = temp.green / 255.0;
	color->blue = temp.blue / 255.0;
	return (0);
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
	point->x = ft_atod(points[0]);
	point->y = ft_atod(points[1]);
	point->z = ft_atod(points[2]);
	ft_free_split(points);
	return (0);
}

int	fill_normalized(char *param, t_point *point, t_objs_type obj)
{
	char	**points;

	points = ft_split(param, ',');
	if (ft_sizeof_split(points) != 3)
	{
		print_error(obj, ERR_NO_PARAM_VEC, 0);
		ft_free_split(points);
		return (1);
	}
	point->x = ft_atod(points[0]);
	point->y = ft_atod(points[1]);
	point->z = ft_atod(points[2]);
	ft_free_split(points);
	if ((point->x < -1.0 || point->x > 1.0)
		|| (point->y < -1.0 || point->y > 1.0)
		|| (point->z < -1.0 || point->z > 1.0))
	{
		print_error(obj, ERR_OUT_RANGE_VEC, 0);
		return (1);
	}
	return (0);
}
