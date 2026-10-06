/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:30:53 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 14:52:59 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*matadd(t_matrix a, t_matrix b)
{
	t_matrix *add;
	int	i;
	int	j;

	if ((a.row != b.row) && (a.col == b.col))
		return (NULL);
	add = (t_matrix *)create_matrix(a.row, a.col);
	i = -1;
	while (++i < a.row)
	{
		j = -1;
		while (++j < a.col)
			add->a[i][j] = a.a[i][j] + b.a[i][j];
	}
	return (add);
}

/*
*/
t_matrix	*matsub(t_matrix a, t_matrix b)
{
	t_matrix *add;
	int	i;
	int	j;

	if ((a.row != b.row) && (a.col == b.col))
		return (NULL);
	add = (t_matrix *)create_matrix(a.row, a.col);
	i = -1;
	while (++i < a.row)
	{
		j = -1;
		while (++j < a.col)
			add->a[i][j] = a.a[i][j] - b.a[i][j];
	}
	return (add);
}
