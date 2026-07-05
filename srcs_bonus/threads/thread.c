/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:44:16 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/04 16:42:41 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_thread	*thread_init(t_window *win, int width, int height, int num_threads)
{
	t_thread	*threads;
	int			range_height;
	int			rest_height;
	int			i;

	threads = ft_calloc(num_threads, sizeof(t_thread));
	range_height = height / num_threads;
	rest_height	= height % num_threads;
	i = 0;
	while (i < num_threads)
	{
		threads[i].scene = win;
		threads[i].id = i + 1;
		threads[i].y_start = range_height * i;
		threads[i].addr = (int *)(win->canva.addr
	+ (win->canva.line_length * threads[i].y_start));
		//threads[i].addr = (int *)((win->canva.addr + (width * range_height * i)));
		threads[i].width = width;
		if (i < num_threads - 1)
			threads[i].height = range_height;
		else
			threads[i].height = range_height + rest_height;
		i++;
	}
	return (threads);
}
