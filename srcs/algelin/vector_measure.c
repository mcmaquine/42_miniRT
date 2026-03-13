/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_measure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:43:16 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/12 22:51:49 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_magnitude(t_point *a)
{
	if (!a)
		return (0);
	return (sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2)));
}

t_point	vec_normalize(t_point *a)
{
	t_point	p;
	double	mag;

	zero_point(&p);
	if (!a)
		return (p);
	mag = vec_magnitude(a);
	if (mag == 0.0)
		return (p);
	p.x = a->x / mag;
	p.y = a->y / mag;
	p.z = a->z / mag;
	return (p);
}
