/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:09:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 13:47:44 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
Apply ambient light rate and ambient light to pixel color
*/
t_color	phong_amb_color(t_window *w, t_hit *hit)
{
	t_color	color;
	t_color	amb_color;
	REAL	light_rate;

	color.red = 0.0;
	color.green = 0.0;
	color.blue = 0.0;
	color.tpcy = 0.0;
	if (!w || !hit)
		return (color);
	amb_color = w->scene_obj->amb->color;
	light_rate = w->scene_obj->amb->light_rate;
	color.red = light_rate * amb_color.red * hit->color.red;
	color.green = light_rate * amb_color.green * hit->color.green;
	color.blue = light_rate * amb_color.blue * hit->color.blue;
	color.tpcy = 0;
	return (color);
}

/*
Computaion of pixel color based on its orthogonality to light source
*/
t_color	phong_diffuse_color(t_window *win, t_hit *hit)
{
	t_color	diffuse;
	t_light	light;
	t_point	light_dir;
	REAL	diff_factor;
	REAL	rate;

	light = *(win->scene_obj->light);
	light_dir = vec_normalize(vec_sub(light.coord, hit->point));
	diff_factor = fmax(0, vec_dot(hit->normal, light_dir));
	rate = light.bright_rate * diff_factor;
	diffuse.red = rate * light.color.red * hit->color.red;
	diffuse.green = rate * light.color.green * hit->color.green;
	diffuse.blue = rate * light.color.blue * hit->color.blue;
	diffuse.tpcy = 0;
	return (diffuse);
}

/*
Computation of final pixel color.
*/
t_color	calculate_illumination(t_window *win, t_hit hit)
{
	t_color	final_color;
	t_color	diffuse;
	t_color	ambient;

	if (hit.t < 0)
		return ((t_color){0 ,0 ,0 ,0});
	if (!is_in_shadow(win, &hit))
		diffuse = phong_diffuse_color(win, &hit);
	else
		ft_memset(&diffuse, 0, sizeof(t_color));
	ambient = phong_amb_color(win, &hit);
	final_color.red = diffuse.red + ambient.red;
	final_color.green = diffuse.green + ambient.green;
	final_color.blue = diffuse.blue + ambient.blue;
	if (final_color.red > 1.0)
		final_color.red = 1.0;
	if (final_color.green > 1.0)
		final_color.green = 1.0;
	if (final_color.blue > 1.0)
		final_color.blue = 1.0;
	return (final_color);
}

/*
Check if pixel is shadowed by other object
*/
int	is_in_shadow(t_window *win, t_hit *hit)
{
	t_point	light_dir;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	REAL	dist_to_light;

	light_dir = vec_normalize(vec_sub(win->scene_obj->light->coord,\
		hit->point));
	shadow_ray.origin = vec_add(hit->point, vec_scale(light_dir, EPSILON));
	shadow_ray.direction = light_dir;
	dist_to_light = vec_magnitude(vec_sub(win->scene_obj->light->coord,\
		shadow_ray.origin));
	shadow_hit = all_intersections(win, shadow_ray);
	if (shadow_hit.t > EPSILON && shadow_hit.t < dist_to_light)
		return (1);
	else
		return (0);
}

