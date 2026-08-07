/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:03:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 00:10:44 by gabrgarc         ###   ########.fr       */
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
