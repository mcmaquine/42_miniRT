/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 22:48:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/08 11:51:37 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_valid_number(const char *str)
{
	int	has_digit;
	int	has_dot;

	if (!str || !*str)
		return (0);
	has_digit = 0;
	has_dot = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str == '.' && !has_dot)
			has_dot = 1;
		else if (*str >= '0' && *str <= '9')
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit);
}

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
int	fill_coordinate(char *param, t_point *point, t_objs_type obj, int line)
{
	char	**points;

	points = ft_split(param, ',');
	if (ft_sizeof_split(points) != 3)
	{
		print_error(obj, ERR_NO_PARAM_COORDS, line);
		ft_free_split(points);
		return (1);
	}
	if (!is_valid_number(points[0]) || !is_valid_number(points[1])
		|| !is_valid_number(points[2]))
	{
		print_error(obj, ERR_COORDS_INVALID, line);
		ft_free_split(points);
		return (1);
	}
	point->x = ft_atod(points[0]);
	point->y = ft_atod(points[1]);
	point->z = ft_atod(points[2]);
	ft_free_split(points);
	return (0);
}
