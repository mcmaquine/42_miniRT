/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:34:03 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/11 18:26:14 by mmaquine         ###   ########.fr       */
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
//utils
int			free_scene_obj(t_scene **scene_obj);
int			fill_color(char *param, t_color *color);
int			fill_coordinate(char *param, t_point *point, double min,\
	double max);
#endif