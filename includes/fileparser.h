/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:34:03 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/09 20:30:58 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_H
# define FILEPARSER_H

int		free_scene_obj(t_scene **scene_obj);
int	sphere_parser(char **params, t_scene *scene_obj);
int	plane_parser(char **params, t_scene *scene_obj);
int	cilinder_parser(char **params, t_scene *scene_obj);
int	amb_light_parser(char **params, t_scene *scene_obj);
int	cam_parser(char **params, t_scene *scene_obj);
int	light_parser(char **params, t_scene *scene_obj);
#endif