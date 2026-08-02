/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:31:18 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/27 17:25:28 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	helper_parse_cylinder(char **params, t_cylinder	*cyl);

/*
Parses a sphere object
*/
int	sphere_parser(char **params, t_scene *scene_obj)
{
	t_sphere	*sphere;

	if (ft_sizeof_split(params) != 4)
	{
		print_error(OBJ_SPHERE, ERR_NO_INFORMATION, 0);
		return (1);
	}
	sphere = ft_calloc(1, sizeof(t_sphere));
	sphere->type.base = SPHERE;
	sphere->diam = ft_atod(params[2]);
	if (sphere->diam <= 0.0)
	{
		print_error(OBJ_SPHERE, ERR_DIAMETER_NEGATIVE, 0);
		free(sphere);
		return (1);	
	}
	if (fill_coordinate(params[1], &(sphere->center), OBJ_SPHERE)
		|| fill_color(params[3], &(sphere->color), OBJ_SPHERE))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&(scene_obj->objs)[SPHERE], ft_lstnew(sphere));
	return (0);
}

/*
Parse a plane object
*/
int	plane_parser(char **params, t_scene *scene_obj)
{
	t_plane	*plane;

	if (ft_sizeof_split(params) != 4)
	{
		print_error(OBJ_PLANE, ERR_NO_INFORMATION, 0);
		return (1);
	}
	plane = ft_calloc(1, sizeof(t_plane));
	plane->type.base = PLANE;
	if (fill_coordinate(params[1], &(plane->a_point), OBJ_PLANE)
		|| fill_normalized(params[2], &(plane->normal), OBJ_PLANE)
		|| fill_color(params[3], &(plane->color), OBJ_PLANE))
	{
		free(plane);
		return (1);
	}
	ft_lstadd_back(&(scene_obj->objs)[PLANE], ft_lstnew(plane));
	return (0);
}

/*
Parse a cilinder object
*/
int	cilinder_parser(char **params, t_scene *scene_obj)
{
	t_cylinder	*cylinder;
	int			error;

	if (ft_sizeof_split(params) != 6)
		return (1);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	cylinder->type.base = CYLINDER;
	error = helper_parse_cylinder(params, cylinder);
	if (error)
	{
		free(cylinder);
		return (error);
	}
	ft_lstadd_back(&(scene_obj->objs)[CYLINDER], ft_lstnew(cylinder));
	return (0);
}

static int	helper_parse_cylinder(char **params, t_cylinder	*cyl)
{
	cyl->diam = ft_atod(params[3]);
	cyl->height = ft_atod(params[4]);
	if (cyl->diam <= 0.0)
		print_error(OBJ_CYLINDER, ERR_DIAMETER_NEGATIVE, 0);
	else if (cyl->height <= 0.0)
		print_error(OBJ_CYLINDER, ERR_HEIGHT_NEGATIVE, 0);
	else if (fill_coordinate(params[1], &(cyl->center), OBJ_CYLINDER)
		|| fill_normalized(params[2], &(cyl->v_axis), OBJ_CYLINDER)
		|| fill_color(params[5], &(cyl->color), OBJ_CYLINDER))
		return (1);
	else
		return (0);
	return (1);
}
