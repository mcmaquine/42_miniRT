/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileparser_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_BONUS_H
# define FILEPARSER_BONUS_H

# define CHECKER_ID "c"
# define BUMP_ID "t"
# define REFLECTION_ID "r"

int	parse_material_bonus(char **params, int index, t_material *material,
		t_objs_type obj);

#endif
