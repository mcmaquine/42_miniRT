/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 21:46:22 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 21:50:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_color_range(t_color temp, t_objs_type obj);
static int	check_color_params(char **colors, t_objs_type obj);
static int	check_vec_range(t_point *point, t_objs_type obj);

/*
Fill struct point and checks its params.
*/
int	fill_color(char *param, t_color *color, t_objs_type obj)
{
	char	**colors;
	t_color	temp;

	colors = ft_split(param, ',');
	if (check_color_params(colors, obj))
	{
		ft_free_split(colors);
		return (1);
	}
	temp.red = ft_atoi(colors[0]);
	temp.green = ft_atoi(colors[1]);
	temp.blue = ft_atoi(colors[2]);
	color->tpcy = 0.0;
	ft_free_split(colors);
	if (check_color_range(temp, obj))
		return (1);
	color->red = temp.red / 255.0;
	color->green = temp.green / 255.0;
	color->blue = temp.blue / 255.0;
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
	if (check_vec_range(point, obj))
		return (1);
	return (0);
}

static int	check_color_range(t_color temp, t_objs_type obj)
{
	if ((temp.red < 0 || temp.red > 255)
		|| (temp.green < 0 || temp.green > 255)
		|| (temp.blue < 0 || temp.blue > 255))
	{
		print_error(obj, ERR_OUT_RANGE_COLOR, 0);
		return (1);
	}
	return (0);
}

static int	check_color_params(char **colors, t_objs_type obj)
{
	if (ft_sizeof_split(colors) != 3)
	{
		print_error(obj, ERR_NO_PARAM_COLOR, 0);
		return (1);
	}
	if (!is_valid_number(colors[0]) || !is_valid_number(colors[1])
		|| !is_valid_number(colors[2]))
	{
		print_error(obj, ERR_OUT_RANGE_COLOR, 0);
		return (1);
	}
	return (0);
}

static int	check_vec_range(t_point *point, t_objs_type obj)
{
	if ((point->x < -1.0 || point->x > 1.0)
		|| (point->y < -1.0 || point->y > 1.0)
		|| (point->z < -1.0 || point->z > 1.0))
	{
		print_error(obj, ERR_OUT_RANGE_VEC, 0);
		return (1);
	}
	return (0);
}
