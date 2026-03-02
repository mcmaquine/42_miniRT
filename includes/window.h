/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:15:07 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/02 17:21:47 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "minirt.h"
void	*create_window(t_window *w, int width, int height);
void	paint_pixel(t_window *w, int x, int y, unsigned int color);
void	clear_canva(t_window *w);
#endif