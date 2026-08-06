/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:46:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/06 15:45:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef void	(*t_objs)(t_scene_obj *obj);

double		to_radians(double degree);
void		calc_components(t_scene *scene);
void		free_window(t_window *win);
double		real_min(double x, double y, double z);
double		real_max(double x, double y, double z);
long		get_current_time(void);
t_scene_obj	**array_objs(t_list *objs[], int n);
int			count_objs(t_list *objs[]);
void		clear_cone(void *obj);
#endif
