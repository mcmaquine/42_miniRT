/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:24:33 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 01:18:57 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	real_max(double x, double y, double z)
{
	double	bigger;

	bigger = x;
	if (y > bigger)
		bigger = y;
	if (z > bigger)
		bigger = z;
	return (bigger);
}
