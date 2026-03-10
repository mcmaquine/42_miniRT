/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:22:38 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/09 21:24:52 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	amb_light_parser(char **params, t_scene *scene_obj)
{
	char	**colors;

	if (ft_sizeof_split(params) != 3 || scene_obj->amb != NULL)
		return (1);
	scene_obj->amb = ft_calloc(1, sizeof(t_amb_light));
	scene_obj->amb->type = AMBIENT_LIGHT;
	scene_obj->amb->light_rate = ft_atod(params[1]);
	if (scene_obj->amb->light_rate < 0.0 || scene_obj->amb->light_rate > 1.0)
	colors = ft_split(params[2], ',');
	if (ft_sizeof_split(colors) != 3)
	{
		ft_free_split(colors);
		return (1);
	}
	scene_obj->amb->color.red = ft_atoi(colors[0]);
	scene_obj->amb->color.green = ft_atoi(colors[1]);
	scene_obj->amb->color.blue = ft_atoi(colors[2]);
	ft_free_split(colors);
	if ((scene_obj->amb->color.red < 0 || scene_obj->amb->color.red > 255)
	|| (scene_obj->amb->color.green < 0 || scene_obj->amb->color.green > 255)
	|| (scene_obj->amb->color.blue < 0 || scene_obj->amb->color.blue > 255))
		return (1);
	return (0);
}

int	cam_parser(char **params, t_scene *scene_obj)
{
	;
}

int	light_parser(char **params, t_scene *scene_obj)
{
	;
}