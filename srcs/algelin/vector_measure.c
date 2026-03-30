/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_measure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:43:16 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/29 20:16:34 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec_magnitude(t_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_point	vec_normalize(t_point a)
{
	t_point	p;
	double	mag;

	mag = vec_magnitude(a);
	zero_point(&p);
	if (!ft_dcmp(mag, 0.0, 1e-9))
		return (p);
	p.x = a.x / mag;
	p.y = a.y / mag;
	p.z = a.z / mag;
	return (p);
}
