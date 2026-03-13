/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:42:56 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/12 22:44:15 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*new_point(double x, double y, double z)
{
	t_point	*p;

	p = ft_calloc(1, sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
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
