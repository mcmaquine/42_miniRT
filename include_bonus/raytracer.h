/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:57 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/06 00:09:30 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H
# define MAX_REFLECTION_DEPTH 4

t_hit	all_intersections(t_window *win, t_ray ray);
t_ray	generate_ray(t_window *win, int px, int py);
t_hit	intersect_plane(t_window *win, t_ray ray);
t_hit	intersect_sphere(t_window *win, t_ray ray);
t_hit	intersect_cylinder(t_window *win, t_ray);
t_hit	full_intersection_cylinder(t_cylinder *cyl, t_ray ray);
t_hit	intersect_cone(t_window *win, t_ray ray);
t_hit	full_intersection_sphere(t_sphere *sph, t_ray ray);
void	calculate_normal(t_hit *hit, t_ray ray);
// Phong
t_color	phong_diffuse_color(t_window *win, t_hit *hit);
t_color	phong_amb_color(t_window *w, t_hit *hit);
t_color	calculate_illumination(t_window *win, t_hit hit);
int		is_in_shadow(t_window *win, t_hit *hit);
//	texture
void		apply_texture_bonus(t_hit *hit);
t_material	*get_material_bonus(t_scene_obj *obj);
t_color		trace_color_bonus(t_window *win, t_ray ray, int depth);
//utils
double 	roots(double a, double b, double c);
void	init_t_hit(t_hit *hit, double t);
t_hit	circular_plane_intersec(t_plane *p, double radius, t_ray r);

#endif
