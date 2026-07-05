/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:46:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 17:27:34 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef void	(*t_objs)(t_scene_obj *obj);

REAL	to_radians(REAL degree);
void	calc_components(t_scene *scene);
void	free_window(t_window *win);
long	get_current_time(void);

#endif
