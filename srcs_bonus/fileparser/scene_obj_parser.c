/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:31:18 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/08 15:44:56 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	parse_cylinder_bonus(char **params, t_cylinder *cylinder, int line);
static int	fill_sphere_diameter(char *param, t_sphere *sphere, int line);

/*
Parses a sphere object
*/
int	sphere_parser(char **params, t_scene *scene_obj)
{
	t_sphere	*sph;
	int			idx_line[2];

	idx_line[0] = 4;
	idx_line[1] = scene_obj->line;
	if (ft_sizeof_split(params) < 4)
		return (print_error(OBJ_SPHERE, ERR_NO_INFORMATION, scene_obj->line));
	sph = ft_calloc(1, sizeof(t_sphere));
	sph->type.base = SPHERE;
	if (fill_sphere_diameter(params[2], sph, scene_obj->line))
	{
		free(sph);
		return (1);
	}
	if (fill_coordinate(params[1], &(sph->center), OBJ_SPHERE,
			scene_obj->line)
		|| fill_color(params[3], &(sph->color), OBJ_SPHERE,
			scene_obj->line)
		|| parse_material_bonus(params, idx_line, &sph->material, OBJ_SPHERE))
	{
		free(sph);
		return (1);
	}
	ft_lstadd_back(&(scene_obj->objs)[SPHERE], ft_lstnew(sph));
	return (0);
}

static int	fill_sphere_diameter(char *param, t_sphere *sphere, int line)
{
	if (!is_valid_real(param))
		sphere->diam = -1;
	else
		sphere->diam = ft_atod(param);
	if (sphere->diam <= 0.0)
	{
		print_error(OBJ_SPHERE, ERR_DIAMETER_NEGATIVE, line);
		return (1);
	}
	return (0);
}

/*
Parse a plane object
*/
int	plane_parser(char **params, t_scene *scene_obj)
{
	t_plane	*plane;
	int		idx_line[2];

	idx_line[0] = 4;
	idx_line[1] = scene_obj->line;
	if (ft_sizeof_split(params) < 4)
	{
		print_error(OBJ_PLANE, ERR_NO_INFORMATION, scene_obj->line);
		return (1);
	}
	plane = ft_calloc(1, sizeof(t_plane));
	plane->type.base = PLANE;
	if (fill_coordinate(params[1], &(plane->a_point), OBJ_PLANE,
			scene_obj->line)
		|| fill_normalized(params[2], &(plane->normal), OBJ_PLANE,
			scene_obj->line)
		|| fill_color(params[3], &(plane->color), OBJ_PLANE,
			scene_obj->line)
		|| parse_material_bonus(params, idx_line, &plane->material, OBJ_PLANE))
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

	if (ft_sizeof_split(params) < 6)
		return (print_error(OBJ_CYLINDER, ERR_NO_INFORMATION, scene_obj->line));
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	cylinder->type.base = CYLINDER;
	if (parse_cylinder_bonus(params, cylinder, scene_obj->line))
	{
		free(cylinder);
		return (1);
	}
	ft_lstadd_back(&(scene_obj->objs)[CYLINDER], ft_lstnew(cylinder));
	return (0);
}

static int	parse_cylinder_bonus(char **params, t_cylinder *cylinder, int line)
{
	int	idx_line[2];

	idx_line[0] = 6;
	idx_line[1] = line;
	if (!is_valid_real(params[3]) || !is_valid_real(params[4]))
		return (print_error(OBJ_CYLINDER, ERR_NO_INFORMATION, line));
	cylinder->diam = ft_atod(params[3]);
	cylinder->height = ft_atod(params[4]);
	if (cylinder->diam <= 0.0)
		return (print_error(OBJ_CYLINDER, ERR_DIAMETER_NEGATIVE, line));
	if (cylinder->height <= 0.0)
		return (print_error(OBJ_CYLINDER, ERR_NO_PARAM_HEIGHT, line));
	if (fill_coordinate(params[1], &cylinder->center, OBJ_CYLINDER, line)
		|| fill_normalized(params[2], &cylinder->v_axis, OBJ_CYLINDER,
			line)
		|| fill_color(params[5], &cylinder->color, OBJ_CYLINDER, line)
		|| parse_material_bonus(params, idx_line, &cylinder->material,
			OBJ_CYLINDER))
		return (1);
	return (0);
}
