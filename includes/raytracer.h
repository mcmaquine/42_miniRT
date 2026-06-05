/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:57 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/05 15:12:16 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

t_hit	all_intersections(t_window *win, int px, int py);
t_ray	generate_ray(t_window *win, int px, int py);
t_hit	intersect_plane(t_window *win, t_ray ray);
t_hit	intersect_sphere(t_window *win, t_ray ray);
t_hit	intersect_cylinder(t_window *win, t_ray);
// Phong
t_color	calc_diffuse(t_window *win, t_hit *hit);
t_color	calc_ambient(t_window *win, t_hit *hit);
//utils
REAL 	roots(REAL a, REAL b, REAL c);
void	init_t_hit(t_hit *hit, REAL t);
#endif