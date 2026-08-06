/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 18:50:29 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytracer_bonus.h"

t_color	phong_amb_color(t_window *win, t_hit *hit)
{
	t_color	color;
	t_color	amb_color;
	REAL	light_rate;

	ft_memset(&color, 0, sizeof(t_color));
	if (!win || !hit)
		return (color);
	amb_color = win->scene_obj->amb->color;
	light_rate = win->scene_obj->amb->light_rate;
	color.red = light_rate * amb_color.red * hit->color.red;
	color.green = light_rate * amb_color.green * hit->color.green;
	color.blue = light_rate * amb_color.blue * hit->color.blue;
	return (color);
}

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

static t_color	phong_specular_color(t_window *win, t_hit *hit)
{
	t_color	specular;
	t_point	light_dir;
	t_point	view_dir;
	t_point	reflect_dir;
	REAL	factor;

	ft_memset(&specular, 0, sizeof(t_color));
	light_dir = vec_normalize(vec_sub(win->scene_obj->light->coord,
				hit->point));
	factor = vec_dot(hit->normal, light_dir);
	if (factor <= 0)
		return (specular);
	reflect_dir = vec_sub(vec_scale(hit->normal, 2 * factor), light_dir);
	view_dir = vec_normalize(vec_sub(hit->view_origin, hit->point));
	factor = pow(fmax(0, vec_dot(reflect_dir, view_dir)), SHININESS);
	factor *= win->scene_obj->light->bright_rate * SPECULAR_STRENGTH;
	specular.red = factor * win->scene_obj->light->color.red;
	specular.green = factor * win->scene_obj->light->color.green;
	specular.blue = factor * win->scene_obj->light->color.blue;
	return (specular);
}

t_color	calculate_illumination(t_window *win, t_hit hit)
{
	t_color	final_color;
	t_color	diffuse;
	t_color	ambient;
	t_color	specular;

	if (hit.t < 0)
		return ((t_color){0, 0, 0, 0});
	apply_texture_bonus(&hit);
	ambient = phong_amb_color(win, &hit);
	ft_memset(&diffuse, 0, sizeof(t_color));
	ft_memset(&specular, 0, sizeof(t_color));
	if (!is_in_shadow(win, &hit))
	{
		diffuse = phong_diffuse_color(win, &hit);
		specular = phong_specular_color(win, &hit);
	}
	final_color.tpcy = 0;
	final_color.red = fmin(1, ambient.red + diffuse.red + specular.red);
	final_color.green = fmin(1, ambient.green + diffuse.green + specular.green);
	final_color.blue = fmin(1, ambient.blue + diffuse.blue + specular.blue);
	return (final_color);
}

int	is_in_shadow(t_window *win, t_hit *hit)
{
	t_point	light_dir;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	REAL	dist_to_light;

	light_dir = vec_normalize(vec_sub(win->scene_obj->light->coord,
				hit->point));
	shadow_ray.origin = vec_add(hit->point, vec_scale(light_dir, EPSILON));
	shadow_ray.direction = light_dir;
	dist_to_light = vec_magnitude(vec_sub(win->scene_obj->light->coord,
				shadow_ray.origin));
	shadow_hit = all_intersections(win, shadow_ray);
	if (shadow_hit.t > EPSILON && shadow_hit.t < dist_to_light)
		return (1);
	return (0);
}
