/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:42:56 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 11:24:05 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	fill_point(REAL x, REAL y, REAL z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_point	copy_point(t_point *a)
{
	t_point	p;

	zero_point(&p);
	if (!a)
		return (p);
	p.x = a->x;
	p.y = a->y;
	p.z = a->z;
	return (p);
}

void	zero_point(t_point *p)
{
	if (!p)
		return ;
	p->x = 0;
	p->y = 0;
	p->z = 0;
}
