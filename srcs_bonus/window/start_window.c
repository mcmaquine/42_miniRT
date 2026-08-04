/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:05:56 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:40:48 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	start_window(t_window *win, int width, int height)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (1);
	win->win = mlx_new_window(win->mlx, width, height, "miniRT");
	if (!win->win)
		return (1);
	win->canva.img = mlx_new_image(win->mlx, width, height);
	if (!win->canva.img)
		return (1);
	win->canva.addr = mlx_get_data_addr(win->canva.img, \
&win->canva.bits_per_pixel, &win->canva.line_length, &win->canva.endian);
	win->width = WIDTH;
	win->height = HEIGHT;
	events(win);
	return (0);
}
