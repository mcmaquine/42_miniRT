/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:57 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/29 17:23:24 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

t_hit	all_intersections(t_window *win, t_ray ray);
t_ray	generate_ray(t_window *win, int px, int py);
t_hit	intersect_plane(t_window *win, t_ray ray);
t_hit	intersect_sphere(t_window *win, t_ray ray);
t_hit	intersect_cylinder(t_window *win, t_ray);
void	calculate_normal(t_hit *hit, t_ray ray);
t_hit	full_intersection_sphere(t_sphere *sphere, t_ray ray);
t_hit	full_intersection_cylinder(t_cylinder *cyl, t_ray ray);
// Phong
t_color	phong_diffuse_color(t_window *win, t_hit *hit);
t_color	phong_amb_color(t_window *w, t_hit *hit);
t_color	calculate_illumination(t_window *win, t_hit hit);
int		is_in_shadow(t_window *win, t_hit *hit);
//utils
double 	roots(double a, double b, double c);
void	init_t_hit(t_hit *hit, double t);

#endif
