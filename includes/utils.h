/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:46:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/27 11:59:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef void	(*t_objs)(t_scene_obj *obj);

REAL	to_radians(REAL degree);
void	calc_components(t_scene *scene);
void	free_window(t_window *win);
void	free_scene(t_scene *scene);
void	free_mlx(void *mlx, void *win, void *img);
void	clear_sphere(void *obj);
void	clear_plane(void *obj);
void	clear_cylinder(void *obj);

#endif
