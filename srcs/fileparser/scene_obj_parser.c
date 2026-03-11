/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:31:18 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/11 19:40:25 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	helper_parse_cilinder(char **params, t_scene *scene_obj, t_cilinder\
	*cil);

/*
Parses a sphere object
*/
int	sphere_parser(char **params, t_scene *scene_obj)
{
	t_sphere	*sphere;

	if (ft_sizeof_split(params) != 4)
		return (1);
	sphere = ft_calloc(1, sizeof(t_sphere));
	sphere->type = SPHERE;
	sphere->diam = ft_atod(params[2]);
	if (sphere->diam == 0.0)
	{
		free(sphere);
		return (1);	
	}
	if (fill_coordinate(params[1], &(sphere->center), 0, 0))
	{
		free(sphere);
		return (1);
	}
	if (fill_color(params[3], &(sphere->color)))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&(scene_obj->objs), sphere);
	return (0);
}

/*
Parse a plane object
*/
int	plane_parser(char **params, t_scene *scene_obj)
{
	t_plane	*plane;

	if (ft_sizeof_split(params) != 4)
		return (1);
	plane = ft_calloc(1, sizeof(t_plane));
	plane->type = PLANE;
	if (fill_coordinate(params[1], &(plane->a_point), 0, 0))
	{
		free(plane);
		return (1);
	}
	if (fill_coordinate(params[2], &(plane->normal), -1.0, 1.0))
	{
		free(plane);
		return (1);
	}
	if (fill_color(params[3], &(plane->color)))
	{
		free(plane);
		return (1);
	}
	ft_lstadd_back(&(scene_obj), plane);
	return (0);
}

/*
Parse a cilinder object
*/
int	cilinder_parser(char **params, t_scene *scene_obj)
{
	t_cilinder	*cilinder;
	int			error;

	if (ft_sizeof_split(params) != 6)
		return (1);
	cilinder = ft_calloc(1, sizeof(t_cilinder));
	error = helper_parse_cilinder(params, scene_obj, cilinder);
	if (error)
	{
		free(cilinder);
		return (error);
	}
	ft_lstadd_back(&(scene_obj->objs), cilinder);
	return (0);
}

static int	helper_parse_cilinder(char **params, t_scene *scene_obj, t_cilinder\
	*cil)
{
	cil->diam = ft_atod(params[3]);
	cil->height = ft_atod(params[4]);
	if (cil->diam == 0.0 || cil->height == 0.0)
	{
		free(cil);
		return (1);
	}
	if (fill_coordinate(params[1], &(cil->center), 0, 0))
	{
		free(cil);
		return (1);
	}
	if (fill_coordinate(params[2], &(cil->v_axis), -1.0, 1.0))
	{
		free(cil);
		return (1);
	}
	if (fill_color(params[5], &(cil->color)))
	{
		free(cil);
		return (1);
	}
	return (0);
}
