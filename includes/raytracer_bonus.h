/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_BONUS_H
# define RAYTRACER_BONUS_H

# define MAX_REFLECTION_DEPTH 4

void	apply_texture_bonus(t_hit *hit);
t_material	*get_material_bonus(t_scene_obj *obj);
t_color	trace_color_bonus(t_window *win, t_ray ray, int depth);

#endif
