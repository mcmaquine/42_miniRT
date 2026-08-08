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

static int	material_error(t_objs_type obj, int line)
{
	print_error(obj, ERR_NO_INFORMATION, line);
	return (1);
}

static int	is_checker_id(char *param)
{
	if (!ft_strcmp(param, CHECKER_ID))
		return (1);
	if (!ft_strcmp(param, "check"))
		return (1);
	return (0);
}

static int	parse_checker(char **params, int *index, t_material *material,
		t_objs_type obj, int line)
{
	if (!ft_strcmp(params[*index], "check")
		&& (!params[*index + 1] || !params[*index + 2]))
	{
		fill_color("255,255,255", &material->checker_color, obj, line);
		material->checker_scale = 1.0;
		material->pattern = PATTERN_CHECKER;
		*index += 1;
		return (0);
	}
	if (!params[*index + 1] || !params[*index + 2])
		return (material_error(obj, line));
	if (fill_color(params[*index + 1], &material->checker_color, obj, line))
		return (1);
	if (!is_valid_real(params[*index + 2]))
		return (material_error(obj, line));
	material->checker_scale = ft_atod(params[*index + 2]);
	if (material->checker_scale <= 0.0)
		return (material_error(obj, line));
	material->pattern = PATTERN_CHECKER;
	*index += 3;
	return (0);
}

static int	parse_reflection(char **params, int *index, t_material *material,
		t_objs_type obj, int line)
{
	if (!params[*index + 1] || !is_valid_real(params[*index + 1]))
		return (material_error(obj, line));
	material->reflection = ft_atod(params[*index + 1]);
	if (material->reflection < 0.0 || material->reflection > 1.0)
		return (material_error(obj, line));
	*index += 2;
	return (0);
}

int	parse_material_bonus(char **params, int index, t_material *material,
		t_objs_type obj, int line)
{
	material->pattern = PATTERN_NONE;
	material->checker_scale = 1.0;
	material->reflection = 0.0;
	while (params[index])
	{
		if (is_checker_id(params[index]))
		{
			if (parse_checker(params, &index, material, obj, line))
				return (1);
		}
		else if (!ft_strcmp(params[index], REFLECTION_ID))
		{
			if (parse_reflection(params, &index, material, obj, line))
				return (1);
		}
		else
			return (material_error(obj, line));
	}
	return (0);
}
