/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/06 22:05:46 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	add_light_color(t_window *win, t_hit *hit, t_light *light,
				t_color *color);

t_color	phong_amb_color(t_window *win, t_hit *hit)
{
	t_color	color;
	t_color	amb_color;
	double	light_rate;

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
	t_light	*light;
	t_list	*node;
	t_point	light_dir;
	double	diff_factor;

	ft_memset(&diffuse, 0, sizeof(t_color));
	node = win->scene_obj->light;
	while (node)
	{
		light = (t_light *)node->content;
		light_dir = vec_normalize(vec_sub(light->coord, hit->point));
		diff_factor = fmax(0, vec_dot(hit->normal, light_dir));
		diff_factor *= light->bright_rate;
		diffuse.red += diff_factor * light->color.red * hit->color.red;
		diffuse.green += diff_factor * light->color.green * hit->color.green;
		diffuse.blue += diff_factor * light->color.blue * hit->color.blue;
		node = node->next;
	}
	return (diffuse);
}

t_color	calculate_illumination(t_window *win, t_hit hit)
{
	t_color	final_color;
	t_color	ambient;
	t_list	*node;
	t_light	*light;

	if (hit.t < 0)
		return ((t_color){0, 0, 0, 0});
	apply_texture_bonus(&hit);
	ambient = phong_amb_color(win, &hit);
	final_color = ambient;
	node = win->scene_obj->light;
	while (node)
	{
		light = (t_light *)node->content;
		if (!is_in_shadow(win, &hit, light))
			add_light_color(win, &hit, light, &final_color);
		node = node->next;
	}
	final_color.tpcy = 0;
	final_color.red = fmin(1, final_color.red);
	final_color.green = fmin(1, final_color.green);
	final_color.blue = fmin(1, final_color.blue);
	return (final_color);
}

int	is_in_shadow(t_window *win, t_hit *hit, t_light *light)
{
	t_point	light_dir;
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	dist_to_light;

	light_dir = vec_normalize(vec_sub(light->coord, hit->point));
	shadow_ray.origin = vec_add(hit->point, vec_scale(light_dir, EPSILON));
	shadow_ray.direction = light_dir;
	dist_to_light = vec_magnitude(vec_sub(light->coord, shadow_ray.origin));
	shadow_hit = all_intersections(win, shadow_ray);
	if (shadow_hit.t > EPSILON && shadow_hit.t < dist_to_light)
		return (1);
	return (0);
}

static void	add_light_color(t_window *win, t_hit *hit, t_light *light,
				t_color *color)
{
	t_point	light_dir;
	t_point	view_dir;
	t_point	reflect_dir;
	double	factor;
	double	rate;

	light_dir = vec_normalize(vec_sub(light->coord, hit->point));
	factor = vec_dot(hit->normal, light_dir);
	if (factor <= 0)
		return ;
	rate = light->bright_rate * factor;
	color->red += rate * light->color.red * hit->color.red;
	color->green += rate * light->color.green * hit->color.green;
	color->blue += rate * light->color.blue * hit->color.blue;
	reflect_dir = vec_sub(vec_scale(hit->normal, 2.0 * factor), light_dir);
	view_dir = vec_normalize(vec_sub(hit->view_origin, hit->point));
	factor = pow(fmax(0, vec_dot(reflect_dir, view_dir)), SHININESS);
	rate = factor * light->bright_rate * SPECULAR_STRENGTH;
	color->red += rate * light->color.red;
	color->green += rate * light->color.green;
	color->blue += rate * light->color.blue;
	(void)win;
}
