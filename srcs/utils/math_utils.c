/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:38:21 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/30 17:51:41 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Converts degree to radians
*/
double to_radians(double degree)
{
	return (degree * (M_PI / 180.0));
}
