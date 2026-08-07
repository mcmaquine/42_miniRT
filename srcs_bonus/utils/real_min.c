/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:24:29 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 01:19:09 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	real_min(double x, double y, double z)
{
	double	less;

	less = x;
	if (y < less)
		less = y;
	if (z < less)
		less = z;
	return (less);
}
