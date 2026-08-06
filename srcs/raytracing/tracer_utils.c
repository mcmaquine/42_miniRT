/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:15:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/29 17:31:51 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Calculate roots from 2nd degree equation, givens its constants a, b and c.
	Returns the least root or (-1) if no real roots exists.
*/
double roots(double a, double b, double c)
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
