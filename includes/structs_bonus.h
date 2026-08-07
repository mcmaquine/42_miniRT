/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 20:53:24 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef enum e_pattern
{
	PATTERN_NONE,
	PATTERN_CHECKER
}	t_pattern;

typedef struct s_material
{
	t_pattern	pattern;
	t_color		checker_color;
	double		checker_scale;
	char		*bump_path;
	double		bump_strength;
	double		reflection;
}	t_material;

#endif
