/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:24:58 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 11:24:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Create a matrix initilizing its values with zero
*/
void	*create_matrix(int rows, int cols)
{
	int			i;
	t_matrix	*m;

	if (!rows || !cols)
		return (NULL);
	m = ft_calloc(1, sizeof(t_matrix));
	if (!m)
		return (NULL);
	m->a = ft_calloc(rows, sizeof(REAL *));
	if (!m->a)
		return (NULL);
	i = -1;
	while (++i < rows)
		m->a[i] = ft_calloc(cols, sizeof(REAL));
	m->col = cols;
	m->row = rows;
	return (m);
}

void	free_matrix(t_matrix *m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < m->row)
	{
		free(m->a[i]);
		i++;
	}
	free(m->a);
	free(m);
}

/*
Multiply two matrixes.
Returns matrix product of the operatrion. NULL if operations not possible.
*/
t_matrix	*matmul(t_matrix a, t_matrix b)
{
	t_matrix	*c;
	int			i;
	int			j;
	int			k;

	if (a.col != b.row)
		return (NULL);
	c = create_matrix(a.row, b.col);
	if (!c)
		return (c);
	i = -1;
	while (++i < a.row)
	{
		j = -1;
		while (++j < b.col)
		{
			k = -1;
			while (++k < a.col)
				c->a[i][j] = fma(a.a[i][k], b.a[k][j], c->a[i][j]);
		}
	}
	return (c);
}
