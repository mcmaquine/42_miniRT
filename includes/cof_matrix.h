/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cof_matrix.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:15:21 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/02 17:29:26 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COF_MATRIX_H
# define COF_MATRIX_H

/*
Context for cofactor calculation
*/
typedef struct s_cof_ctx
{
	t_matrix	src;
	t_matrix	*tmp;
	int			ord;
	int			ci;
	int			cj;
}	t_cof_ctx;

#endif
