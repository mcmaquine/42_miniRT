/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:02:22 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 18:24:26 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_sign(int ci, int cj);
static void	fill_row(t_cof_ctx *ctx, int row, int x);
static void	fill_matrix(t_cof_ctx *ctx);

/*
Calculate a cofactor of a square matrix for the element (ci,cj). Return 0 if is
not a squared matrix.
*/
double	cofactor(t_matrix m, int ci, int cj)
{
	t_cof_ctx	ctx;
	double		cof;

	if (m.row != m.col)
		return (0);
	ctx.src = m;
	ctx.ord = m.row - 1;
	ctx.ci = ci;
	ctx.cj = cj;
	ctx.tmp = create_matrix(ctx.ord - 1, ctx.ord - 1);
	if (!ctx.tmp)
		return (0);
	fill_matrix(&ctx);
	cof = get_sign(ci, cj) * determinant(*(ctx.tmp));
	free(ctx.tmp);
	return (cof);
}

static void	fill_row(t_cof_ctx *ctx, int row, int x)
{
	int	j;
	int	y;

	j = 0;
	y = 0;
	while (j < ctx->ord)
	{
		if (j != ctx->cj && j <= ctx->ord - 1)
		{
			ctx->tmp->a[x][y] = ctx->src.a[row][j];
			y++;
		}
		j++;
	}
}

static void	fill_matrix(t_cof_ctx *ctx)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < ctx->ord)
	{
		if (i != ctx->ci && i <= ctx->ord - 1)
		{
			fill_row(ctx, i, x);
			x++;
		}
		i++;
	}
}

static int	get_sign(int ci, int cj)
{
	int	pot;

	if ((ci + cj) % 2 == 0)
		pot = 1;
	else
		pot = -1;
	return (pot);
}
