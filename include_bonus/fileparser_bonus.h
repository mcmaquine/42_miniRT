/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileparser_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/05 22:59:16 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEPARSER_BONUS_H
# define FILEPARSER_BONUS_H

# define CHECKER_ID "c"
# define BUMP_ID "t"
# define REFLECTION_ID "r"

int	parse_material_bonus(char **params, int index, t_material *material,
		t_objs_type obj);
t_scene	*read_file(char *filename);
int		sphere_parser(char **params, t_scene *scene_obj);
int		plane_parser(char **params, t_scene *scene_obj);
int		cilinder_parser(char **params, t_scene *scene_obj);
int		cone_parser(char **params, t_scene *scene_obj);
int		amb_light_parser(char **params, t_scene *scene_obj);
int		cam_parser(char **params, t_scene *scene_obj);
int		light_parser(char **params, t_scene *scene_obj);
void	calc_components(t_scene *scene);
void	free_scene_obj(t_scene **scene_obj);
int		fill_color(char *param, t_color *color, t_objs_type obj);
void	print_error(t_objs_type obj, t_error_option option, int line);
int		fill_coordinate(char *param, t_point *point, t_objs_type obj);
int		fill_normalized(char *param, t_point *point, t_objs_type obj);
int		is_valid_real(const char *str);

#endif
