/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_obj_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 22:48:33 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/08 12:33:38 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	amb_light_parser(char **params, t_scene *scene_obj)
{
	if (scene_obj->amb != NULL)
	{
		print_error(OBJ_AMBIENT, ERR_NO_UNIQUE, scene_obj->line);
		return (1);
	}
	if (ft_sizeof_split(params) != 3)
	{
		print_error(OBJ_AMBIENT, ERR_NO_INFORMATION, scene_obj->line);
		return (1);
	}
	scene_obj->amb = ft_calloc(1, sizeof(t_amb_light));
	if (!scene_obj->amb)
		return (1);
	scene_obj->amb->type.base = AMBIENT_LIGHT;
	scene_obj->amb->light_rate = ft_atod(params[1]);
	if (scene_obj->amb->light_rate < 0.0 || scene_obj->amb->light_rate > 1.0)
	{
		print_error(OBJ_AMBIENT, ERR_OUT_RANGE_RATIO, scene_obj->line);
		return (1);
	}
	if (fill_color(params[2], &(scene_obj->amb->color), OBJ_AMBIENT,
			scene_obj->line))
		return (1);
	return (0);
}

int	cam_parser(char **params, t_scene *scene_obj)
{
	t_cam	*cam;

	if (scene_obj->cam != NULL)
	{
		print_error(OBJ_CAMERA, ERR_NO_UNIQUE, scene_obj->line);
		return (1);
	}
	if (ft_sizeof_split(params) != 4)
	{
		print_error(OBJ_CAMERA, ERR_NO_INFORMATION, scene_obj->line);
		return (1);
	}
	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		return (1);
	if (fill_cam(params, cam, scene_obj->line))
	{
		free(cam);
		return (1);
	}
	scene_obj->cam = cam;
	return (0);
}

int	light_parser(char **params, t_scene *scene_obj)
{
	t_light	*light;

	if (scene_obj->light != NULL)
	{
		print_error(OBJ_LIGHT, ERR_NO_UNIQUE, scene_obj->line);
		return (1);
	}
	if (ft_sizeof_split(params) != 4)
	{
		print_error(OBJ_LIGHT, ERR_NO_INFORMATION, scene_obj->line);
		return (1);
	}
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (1);
	if (fill_light(params, light, scene_obj->line))
	{
		free(light);
		return (1);
	}
	scene_obj->light = light;
	return (0);
}
