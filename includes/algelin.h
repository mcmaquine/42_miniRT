/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algelin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 21:05:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 18:23:09 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGELIN_H
# define ALGELIN_H
t_point	vec_add(t_point a, t_point b);
t_point	vec_sub(t_point a, t_point b);
t_point	vec_scale(t_point a, double t);
t_point	vec_cross(t_point a, t_point b);
double	vec_dot(t_point a, t_point b);
double	vec_magnitude(t_point a);
t_point	vec_normalize(t_point a);
//matrix functions
double	determinant(t_matrix m);
double	cofactor(t_matrix m, int ci, int cj);
//utils
void	zero_point(t_point *p);
t_point	fill_point(double x, double y, double z);
void	*create_matrix(int rows, int cols);
void	free_matrix(t_matrix *m);
#endif