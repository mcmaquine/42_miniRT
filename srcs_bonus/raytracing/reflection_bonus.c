/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "raytracer_bonus.h"

static t_ray	reflected_ray(t_hit *hit, t_ray incident)
{
	t_ray	reflected;
	double	dot;
	double	side;

	dot = vec_dot(incident.direction, hit->normal);
	reflected.direction = vec_sub(incident.direction,
			vec_scale(hit->normal, 2.0 * dot));
	side = 1.0;
	if (vec_dot(reflected.direction, hit->normal) < 0.0)
		side = -1.0;
	reflected.origin = vec_add(hit->point,
			vec_scale(hit->normal, EPSILON * side));
	return (reflected);
}

static t_color	blend_reflection(t_color local, t_color reflected, double rate)
{
	t_color	color;

	color.tpcy = 0;
	color.red = local.red * (1.0 - rate) + reflected.red * rate;
	color.green = local.green * (1.0 - rate) + reflected.green * rate;
	color.blue = local.blue * (1.0 - rate) + reflected.blue * rate;
	return (color);
}

t_color	trace_color_bonus(t_window *win, t_ray ray, int depth)
{
	t_hit		hit;
	t_color		local;
	t_color		reflected;
	t_material	*material;

	hit = all_intersections(win, ray);
	if (hit.t < 0)
		return ((t_color){0, 0, 0, 0});
	hit.view_origin = ray.origin;
	local = calculate_illumination(win, hit);
	material = get_material_bonus(hit.obj);
	if (depth <= 0 || !material || material->reflection <= 0.0)
		return (local);
	reflected = trace_color_bonus(win, reflected_ray(&hit, ray), depth - 1);
	return (blend_reflection(local, reflected, material->reflection));
}
