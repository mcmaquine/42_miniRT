/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_parser_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/06 15:29:35 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "fileparser_bonus.h"

static int	parse_cylinder_bonus(char **params, t_cylinder *cylinder);

int	sphere_parser(char **params, t_scene *scene)
{
	t_sphere	*sphere;

	if (ft_sizeof_split(params) < 4)
		return (1);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->type.base = SPHERE;
	if (!is_valid_real(params[2]))
		sphere->diam = -1;
	else
		sphere->diam = ft_atod(params[2]);
	if (sphere->diam <= 0.0
		|| fill_coordinate(params[1], &sphere->center, OBJ_SPHERE)
		|| fill_color(params[3], &sphere->color, OBJ_SPHERE)
		|| parse_material_bonus(params, 4, &sphere->material, OBJ_SPHERE))
	{
		free(sphere);
		return (1);
	}
	ft_lstadd_back(&scene->objs[SPHERE], ft_lstnew(sphere));
	return (0);
}

int	plane_parser(char **params, t_scene *scene)
{
	t_plane	*plane;

	if (ft_sizeof_split(params) < 4)
		return (1);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (1);
	plane->type.base = PLANE;
	if (fill_coordinate(params[1], &plane->a_point, OBJ_PLANE)
		|| fill_normalized(params[2], &plane->normal, OBJ_PLANE)
		|| fill_color(params[3], &plane->color, OBJ_PLANE)
		|| parse_material_bonus(params, 4, &plane->material, OBJ_PLANE))
	{
		free(plane);
		return (1);
	}
	ft_lstadd_back(&scene->objs[PLANE], ft_lstnew(plane));
	return (0);
}

int	cilinder_parser(char **params, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (ft_sizeof_split(params) < 6)
		return (1);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	cylinder->type.base = CYLINDER;
	if (parse_cylinder_bonus(params, cylinder))
	{
		free(cylinder);
		return (1);
	}
	ft_lstadd_back(&scene->objs[CYLINDER], ft_lstnew(cylinder));
	return (0);
}

static int	parse_cylinder_bonus(char **params, t_cylinder *cylinder)
{
	if (!is_valid_real(params[3]) || !is_valid_real(params[4]))
		return (1);
	cylinder->diam = ft_atod(params[3]);
	cylinder->height = ft_atod(params[4]);
	if (cylinder->diam <= 0.0 || cylinder->height <= 0.0)
		return (1);
	if (fill_coordinate(params[1], &cylinder->center, OBJ_CYLINDER)
		|| fill_normalized(params[2], &cylinder->v_axis, OBJ_CYLINDER)
		|| fill_color(params[5], &cylinder->color, OBJ_CYLINDER)
		|| parse_material_bonus(params, 6, &cylinder->material,
			OBJ_CYLINDER))
		return (1);
	return (0);
}
