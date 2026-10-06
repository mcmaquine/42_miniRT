/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_obj_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:22:38 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/14 11:13:40 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	amb_light_parser(char **params, t_scene *scene_obj)
{
	if (ft_sizeof_split(params) != 3 || scene_obj->amb != NULL)
		return (1);
	scene_obj->amb = ft_calloc(1, sizeof(t_amb_light));
	scene_obj->amb->type.base = AMBIENT_LIGHT;
	scene_obj->amb->light_rate = ft_atod(params[1]);
	if (scene_obj->amb->light_rate < 0.0 || scene_obj->amb->light_rate > 1.0)
		return (1);
	if (fill_color(params[2], &(scene_obj->amb->color)))
		return (1);
	return (0);
}

int	cam_parser(char **params, t_scene *scene_obj)
{
	t_cam	*cam;

	if (ft_sizeof_split(params) != 4 || scene_obj->cam != NULL)
		return (1);
	cam = ft_calloc(1, sizeof(t_cam));
	cam->type.base = CAMERA;
	cam->fov = ft_atod(params[3]);
	if (cam->fov < 0.0 || cam->fov > 180)
	{
		free(cam);
		return (1);
	}
	if (fill_coordinate(params[1], &(cam->point), 0, 0))
	{
		free(cam);
		return (1);
	}
	if (fill_coordinate(params[2], &(cam->orient), -1.0, 1.0))
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

	if (scene_obj->light != NULL || ft_sizeof_split(params) != 4)
		return (1);
	light = ft_calloc(1, sizeof(t_light));
	light->type.base = LIGHT;
	light->bright_rate = ft_atod(params[2]);
	if (light->bright_rate < 0.0 || light->bright_rate > 1.0)
	{
		free(light);
		return (1);
	}
	if (fill_coordinate(params[1], &(light->coord), 0.0, 0.0))
	{
		free(light);
		return (1);
	}
	if (fill_color(params[3], &(light->color)))
	{
		free(light);
		return (1);
	}
	scene_obj->light = light;
	return (0);
}
