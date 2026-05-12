/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:15:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/29 15:22:34 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Calculate roots from 2nd degree equation, givens its constants a, b and c.
	Returns the least root or (-1) if no real roots exists.
*/
REAL roots(REAL a, REAL b, REAL c)
{
	REAL	delta;
	REAL	sqrt_delta;
	REAL	t1;
	REAL	t2;

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
