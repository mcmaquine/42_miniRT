/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:34:03 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/27 17:22:45 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_H
# define FILEPARSER_H

t_scene*	read_file(char *filename);
int			sphere_parser(char **params, t_scene *scene_obj);
int			plane_parser(char **params, t_scene *scene_obj);
int			cilinder_parser(char **params, t_scene *scene_obj);
int			amb_light_parser(char **params, t_scene *scene_obj);
int			cam_parser(char **params, t_scene *scene_obj);
int			light_parser(char **params, t_scene *scene_obj);
void		calc_components(t_scene *scene);
//utils
void		free_scene_obj(t_scene **scene_obj);
int			is_valid_real(const char *str);
int			fill_color(char *param, t_color *color, t_objs_type obj);
void	print_error(t_objs_type obj, t_error_option option, int line);
int			fill_coordinate(char *param, t_point *point, t_objs_type obj);
int	fill_normalized(char *param, t_point *point, t_objs_type obj);
#endif
