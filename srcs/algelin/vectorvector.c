/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorvector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:07:51 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 10:33:15 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	vec_add(t_point a, t_point b)
{
	t_point	p;

	p.x = a.x + b.x;
	p.y = a.y + b.y;
	p.z = a.z + b.z;
	return (p);
}

t_point	vec_sub(t_point a, t_point b)
{
	t_point p;

	p.x = a.x - b.x;
	p.y = a.y - b.y;
	p.z = a.z - b.z;
	return (p);
}

t_point	vec_scale(t_point a, double t)
{
	t_point	p;

	p.x = a.x * t;
	p.y = a.y * t;
	p.z = a.z * t;
	return (p);
}

t_point	vec_cross(t_point a, t_point b)
{
	t_point	p;

	p.x = a.y * b.z - (b.y * a.z);
	p.y = a.z * b.x - (b.z * a.x);
	p.z = a.x * b.y - (b.x * a.y);
	return (p);
}

double vec_dot(t_point a, t_point b)
{
	double	dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
}
