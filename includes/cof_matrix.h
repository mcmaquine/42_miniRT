/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cof_matrix.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:15:21 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 18:16:39 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COF_CONTEXT_H
# define FT_COF_CONTEXT_H

/*
Contexto para calculo de cofator
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