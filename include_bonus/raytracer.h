/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:57 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:33:11 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

t_hit	all_intersections(t_window *win, t_ray ray);
t_ray	generate_ray(t_window *win, int px, int py);
t_hit	intersect_plane(t_window *win, t_ray ray);
t_hit	intersect_sphere(t_window *win, t_ray ray);
t_hit	intersect_cylinder(t_window *win, t_ray);
t_hit	intersect_cone(t_window *win, t_ray ray);
void	calculate_normal(t_hit *hit, t_ray ray);
t_hit	full_intersection_sphere(t_sphere *sphere, t_ray ray);
t_hit	full_intersection_cylinder(t_cylinder *cyl, t_ray ray);
// Phong
t_color	phong_diffuse_color(t_window *win, t_hit *hit);
t_color	phong_amb_color(t_window *w, t_hit *hit);
t_color	calculate_illumination(t_window *win, t_hit hit);
int		is_in_shadow(t_window *win, t_hit *hit);
//utils
REAL 	roots(REAL a, REAL b, REAL c);
void	init_t_hit(t_hit *hit, REAL t);
t_hit	circular_plane_intersec(t_plane *p, REAL radius, t_ray r);

#endif
