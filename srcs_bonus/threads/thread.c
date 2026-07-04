/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:44:16 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/03 21:29:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	thread_init(t_window *win, int width, int height)
{
	t_thread	*threads;
	int			num_threads;
	int			range_height;
	int			i;

	num_threads = get_num_threads();
	threads = ft_calloc(num_threads, sizeof(t_thread));
	range_height = height / num_thread;
	i = 0;
	while (i < num_threads)
	{
		threads[i].id = i + 1;
		threads[i]->addr = win->canva->addr[width * range_height * (i + 1)];
		threads[i].width = width;
		threads[i].height = range_height;
	}
}
