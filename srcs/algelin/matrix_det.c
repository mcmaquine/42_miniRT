/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_det.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:04:43 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 11:23:57 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static REAL	det2(t_matrix m);
static REAL	det3(t_matrix m);
static REAL	det4(t_matrix m);

/*
Return the determinant of square matrixes up to 4 by 4.
*/
REAL	determinant(t_matrix m)
{
	if (m.col != m.row)
		return (0);
	if (m.row == 1)
		return (m.a[0][0]);
	if (m.row == 2)
		return (det2(m));
	if (m.row == 3)
		return (det3(m));
	if (m.row == 4)
		return (det4(m));
	return (0);
}

static REAL	det2(t_matrix m)
{
	return (m.a[0][0] * m.a[1][1] - m.a[0][1] * m.a[1][0]);
}

static REAL	det3(t_matrix m)
{
	return (\
		(m.a[0][0] * m.a[1][1] * m.a[2][2] + m.a[0][1] * m.a[1][2] * m.a[2][0]\
		+ m.a[0][2] * m.a[1][0] * m.a[2][1])\
		- (m.a[0][2] * m.a[1][1] *  m.a[2][0] + m.a[0][1] * m.a[1][0] *\
		m.a[2][2] + m.a[0][0] * m.a[1][2] * m.a[2][1]));
}

static REAL	det4(t_matrix m)
{
	return ((m.a[0][0] * m.a[1][1] * m.a[2][2] * m.a[3][3] +\
		m.a[0][0] * m.a[1][2] * m.a[2][3] * m.a[3][1] +\
		m.a[0][0] * m.a[1][3] * m.a[2][1] * m.a[3][2] +\
		m.a[0][1] * m.a[1][0] * m.a[2][3] * m.a[3][2] +\
		m.a[0][1] * m.a[1][2] * m.a[2][0] * m.a[3][3] +\
		m.a[0][1] * m.a[1][3] * m.a[2][2] * m.a[3][0] +\
		m.a[0][2] * m.a[1][0] * m.a[2][1] * m.a[3][3] +\
		m.a[0][2] * m.a[1][1] * m.a[2][3] * m.a[3][0] +\
		m.a[0][2] * m.a[1][3] * m.a[2][0] * m.a[3][1] +\
		m.a[0][3] * m.a[1][0] * m.a[2][2] * m.a[3][1] +\
		m.a[0][3] * m.a[1][1] * m.a[2][0] * m.a[3][2] +\
		m.a[0][3] * m.a[1][2] * m.a[2][1] * m.a[3][0])\
		- (m.a[0][0] * m.a[1][1] * m.a[2][3] * m.a[3][2]\
			+ m.a[0][0] * m.a[1][2] * m.a[2][1] * m.a[3][3]
			+ m.a[0][0] * m.a[1][3] * m.a[2][2] * m.a[3][1]
			+ m.a[0][1] * m.a[1][0] * m.a[2][2] * m.a[3][3]
			+ m.a[0][1] * m.a[1][2] * m.a[2][3] * m.a[3][0]
			+ m.a[0][1] * m.a[1][3] * m.a[2][0] * m.a[3][2]
			+ m.a[0][2] * m.a[1][0] * m.a[2][3] * m.a[3][1]
			+ m.a[0][2] * m.a[1][1] * m.a[2][0] * m.a[3][3]
			+ m.a[0][2] * m.a[1][3] * m.a[2][1] * m.a[3][0]
			+ m.a[0][3] * m.a[1][0] * m.a[2][1] * m.a[3][2]
			+ m.a[0][3] * m.a[1][1] * m.a[2][2] * m.a[3][0]
			+ m.a[0][3] * m.a[1][2] * m.a[2][0] * m.a[3][1]));
}
