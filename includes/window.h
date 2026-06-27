/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:15:07 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/27 11:51:09 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "minirt.h"

void	start_window(t_window *win, int width, int height);
void	events(t_window *win);
void	paint_pixel(t_window *w, int x, int y, unsigned int color);
void	clear_canva(t_window *w);

#endif
