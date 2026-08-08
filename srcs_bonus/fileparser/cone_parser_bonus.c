/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:23:37 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/08 15:43:16 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	fill_cone(char **params, t_cone *cone, int line);

int	cone_parser(char **params, t_scene *scene_obj)
{
	t_cone	*cone;
	int		error;

	if (ft_sizeof_split(params) < 6)
	{
		print_error(OBJ_CONE, ERR_NO_INFORMATION, scene_obj->line);
		return (1);
	}
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (1);
	cone->type.base = CONE;
	error = fill_cone(params, cone, scene_obj->line);
	if (error)
	{
		free(cone);
		return (error);
	}
	ft_lstadd_back(&(scene_obj->objs)[CONE], ft_lstnew(cone));
	return (0);
}

static int	fill_cone(char **params, t_cone *cone, int line)
{
	int	idx_line[2];

	idx_line[0] = 6;
	idx_line[1] = line;
	cone->theta = ft_atod(params[3]);
	cone->height = ft_atod(params[4]);
	if (cone->theta <= 1.0 || cone->theta >= 89.0)
		print_error(OBJ_CONE, ERR_OUT_RANGE_ANGLE, line);
	else if (cone->height <= 0.0)
		print_error(OBJ_CONE, ERR_NO_PARAM_HEIGHT, line);
	else if (fill_coordinate(params[1], &(cone->vertex), OBJ_CONE, line)
		|| fill_normalized(params[2], &(cone->v_axis), OBJ_CONE, line)
		|| fill_color(params[5], &(cone->color), OBJ_CONE, line)
		|| parse_material_bonus(params, idx_line, &cone->material, OBJ_CONE))
		return (1);
	else
		return (0);
	return (1);
}
