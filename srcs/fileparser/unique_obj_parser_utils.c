/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_obj_parser_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 22:48:52 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 22:48:52 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_cam(char **params, t_cam *cam)
{
	cam->type.base = CAMERA;
	cam->fov = ft_atod(params[3]);
	if (cam->fov < 0.0 || cam->fov > 180)
	{
		print_error(OBJ_CAMERA, ERR_OUT_RANGE_FOV, 0);
		return (1);
	}
	if (fill_coordinate(params[1], &(cam->point), OBJ_CAMERA)
		|| fill_normalized(params[2], &(cam->orient), OBJ_CAMERA))
		return (1);
	return (0);
}

int	fill_light(char **params, t_light *light)
{
	light->type.base = LIGHT;
	light->bright_rate = ft_atod(params[2]);
	if (light->bright_rate < 0.0 || light->bright_rate > 1.0)
	{
		print_error(OBJ_LIGHT, ERR_OUT_RANGE_BRIGHT, 0);
		return (1);
	}
	if (fill_coordinate(params[1], &(light->coord), OBJ_LIGHT)
		|| fill_color(params[3], &(light->color), OBJ_LIGHT))
		return (1);
	return (0);
}
