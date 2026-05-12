/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:38:57 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/29 14:19:17 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACER_H
# define RAY_TRACER_H

t_plane *find_planes(t_window *win);
t_ray	generate_ray(t_window *win, int px, int py);
REAL	intersect_plane(t_window *win, t_ray ray);
REAL	intersect_sphere(t_window *win, t_ray ray);
REAL	intersect_cylinder(t_window *win, t_ray);
//utils
REAL 	roots(REAL a, REAL b, REAL c);
#endif