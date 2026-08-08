/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 11:05:21 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/04 13:47:51 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	key_map(int keysym, t_window *win);
int	close_program(t_window *win);

void	events(t_window *win)
{
	mlx_hook(win->win, KeyPress, KeyPressMask, key_map, win);
	mlx_hook(win->win, DestroyNotify, StructureNotifyMask, close_program, win);
}

int	key_map(int keysym, t_window *win)
{
	if (keysym == XK_Escape)
		close_program(win);
	return (0);
}

int	close_program(t_window *win)
{
	free_window(win);
	exit(0);
	return (0);
}
