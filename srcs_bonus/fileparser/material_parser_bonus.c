/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/08 15:34:52 by mmaquine         ###   ########.fr       */
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

static int	parse_checker(char **params, int *idx_line, t_material *material,
		t_objs_type obj)
{
	if (!ft_strcmp(params[idx_line[0]], "check")
		&& (!params[idx_line[0] + 1] || !params[idx_line[0] + 2]))
	{
		fill_color("255,255,255", &material->checker_color, obj, idx_line[1]);
		material->checker_scale = 1.0;
		material->pattern = PATTERN_CHECKER;
		idx_line[0] += 1;
		return (0);
	}
	if (!params[idx_line[0] + 1] || !params[idx_line[0] + 2])
		return (1);
	if (fill_color(params[idx_line[0] + 1], &material->checker_color, obj,
			idx_line[1]))
		return (2);
	if (!is_valid_real(params[idx_line[0] + 2]))
		return (1);
	material->checker_scale = ft_atod(params[idx_line[0] + 2]);
	if (material->checker_scale <= 0.0)
		return (1);
	material->pattern = PATTERN_CHECKER;
	idx_line[0] += 3;
	return (0);
}

static int	parse_reflection(char **params, int *idx_line, t_material *material,
		t_objs_type obj)
{
	(void)obj;
	if (!params[idx_line[0] + 1] || !is_valid_real(params[idx_line[0] + 1]))
		return (1);
	material->reflection = ft_atod(params[idx_line[0] + 1]);
	if (material->reflection < 0.0 || material->reflection > 1.0)
		return (1);
	idx_line[0] += 2;
	return (0);
}

int	parse_material_bonus(char **params, int *idx_line, t_material *material,
		t_objs_type obj)
{
	int	error;

	material->pattern = PATTERN_NONE;
	material->checker_scale = 1.0;
	material->reflection = 0.0;
	while (params[idx_line[0]])
	{
		if (is_checker_id(params[idx_line[0]]))
		{
			error = parse_checker(params, idx_line, material, obj);
			if (error == 2)
				return (1);
			if (error)
				return (material_error(obj, idx_line[1]));
		}
		else if (!ft_strcmp(params[idx_line[0]], REFLECTION_ID))
		{
			if (parse_reflection(params, idx_line, material, obj))
				return (material_error(obj, idx_line[1]));
		}
		else
			return (material_error(obj, idx_line[1]));
	}
	return (0);
}
