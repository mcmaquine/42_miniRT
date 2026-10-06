/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algelin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:05:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 15:53:16 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGELIN_H
# define ALGELIN_H
t_point	vec_add(t_point a, t_point b);
t_point	vec_sub(t_point a, t_point b);
t_point	vec_scale(t_point a, REAL t);
t_point	vec_cross(t_point a, t_point b);
REAL	vec_dot(t_point a, t_point b);
REAL	vec_magnitude(t_point a);
t_point	vec_normalize(t_point a);
//matrix functions
REAL	determinant(t_matrix m);
REAL	cofactor(t_matrix m, int ci, int cj);
//utils
void	zero_point(t_point *p);
t_point	fill_point(REAL x, REAL y, REAL z);
void	*create_matrix(int rows, int cols);
void	free_matrix(t_matrix *m);
#endif
