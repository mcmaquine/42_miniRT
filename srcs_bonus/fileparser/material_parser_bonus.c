/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/06 14:46:38 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	material_error(t_objs_type obj)
{
	print_error(obj, ERR_NO_INFORMATION, 0);
	return (1);
}

static int	parse_checker(char **params, int *index, t_material *material,
		t_objs_type obj)
{
	if (!params[*index + 1] || !params[*index + 2])
		return (material_error(obj));
	if (fill_color(params[*index + 1], &material->checker_color, obj))
		return (1);
	if (!is_valid_real(params[*index + 2]))
		return (material_error(obj));
	material->checker_scale = ft_atod(params[*index + 2]);
	if (material->checker_scale <= 0.0)
		return (material_error(obj));
	material->pattern = PATTERN_CHECKER;
	*index += 3;
	return (0);
}

static int	parse_reflection(char **params, int *index, t_material *material,
		t_objs_type obj)
{
	if (!params[*index + 1] || !is_valid_real(params[*index + 1]))
		return (material_error(obj));
	material->reflection = ft_atod(params[*index + 1]);
	if (material->reflection < 0.0 || material->reflection > 1.0)
		return (material_error(obj));
	*index += 2;
	return (0);
}

int	parse_material_bonus(char **params, int index, t_material *material,
		t_objs_type obj)
{
	material->pattern = PATTERN_NONE;
	material->checker_scale = 1.0;
	material->reflection = 0.0;
	while (params[index])
	{
		if (!ft_strcmp(params[index], CHECKER_ID))
		{
			if (parse_checker(params, &index, material, obj))
				return (1);
		}
		else if (!ft_strcmp(params[index], REFLECTION_ID))
		{
			if (parse_reflection(params, &index, material, obj))
				return (1);
		}
		else
			return (material_error(obj));
	}
	return (0);
}
