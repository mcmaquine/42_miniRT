/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:15:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:39:44 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/*
	Calculate roots from 2nd degree equation, givens its constants a, b and c.
	Returns the least root or (-1) if no real roots exists.
*/
double	roots(double a, double b, double c)
{
	double	delta;
	double	sqrt_delta;
	double	t1;
	double	t2;

	delta = b * b - 4 * a * c;
	if (delta < 0.0)
		return (-1);
	sqrt_delta = sqrt(delta);
	t1 = 0.5 * (-b - sqrt_delta) / a;
	t2 = 0.5 * (-b + sqrt_delta) / a;
	if (t1 >= 0.0)
		return (t1);
	else if (t2 >= 0.0)
		return (t2);
	else
		return (-1);
}

void	init_t_hit(t_hit *hit, double t)
{
	hit->color = (t_color){0, 0, 0, 0};
	hit->normal = (t_point){0.0, 0.0, 0.0};
	hit->point = hit->normal;
	hit->t = t;
	hit->obj = NULL;
}

/*
Check if a ray intersects a circular plane.
*/
t_hit	circular_plane_intersec(t_plane *p, double radius, t_ray r)
{
	t_point	pt;
	t_hit	hit;
	double	dot;
	double	dist;

	init_t_hit(&hit, -1);
	if (!p)
		return (hit);
	dot = vec_dot(p->normal, r.direction);
	if (!ft_dcmp(dot, 0.0, 1e-5))
		return (hit);
	hit.t = -vec_dot(p->normal, vec_sub(r.origin, p->a_point)) / dot;
	if (hit.t > 0)
	{
		pt = vec_add(r.origin, vec_scale(r.direction, hit.t));
		dist = vec_magnitude(vec_sub(pt, p->a_point));
		if (dist <= radius)
		{
			hit.obj = (t_scene_obj *)p;
			hit.color = p->color;
		}
		else
			hit.t = -1;
	}
	return (hit);
}
