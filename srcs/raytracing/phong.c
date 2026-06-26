/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:09:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/25 22:40:04 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	phong_amb_color(t_window *w, t_hit *hit)
{
	t_color	color;
	REAL	light_rate;

	color.red = 0.0;
	color.green = 0.0;
	color.blue = 0.0;
	color.tpcy = 0.0;
	if (!w || !hit)
		return (color);
	light_rate = w->scene_obj->amb->light_rate;
	color.red = light_rate * w->scene_obj->amb->color.red * hit->color.red;
	color.green = light_rate * w->scene_obj->amb->color.green * hit->color.green;
	color.blue = light_rate * w->scene_obj->amb->color.blue * hit->color.blue;
	color.tpcy = 0;
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

t_color	calculate_illumination(t_window *win, t_hit hit)
{
	t_color	final_color;
	t_color	diffuse;
	t_color	ambient;

	diffuse = phong_diffuse_color(win, &hit);
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
