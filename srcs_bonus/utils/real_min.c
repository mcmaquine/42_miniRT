/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_min.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:03:53 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 00:11:11 by gabrgarc         ###   ########.fr       */
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
