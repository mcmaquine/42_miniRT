/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:30:22 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/04 16:40:41 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

typedef struct	s_thread
{
	t_window	*scene;
	int			*addr;
	pthread_t	thread_id;
	int			id;
	int			width;
	int			height;
	int			y_start;
}	t_thread;

t_thread	*thread_init(t_window *win, int width, int height, int num_threads);
void		*routine(void *arg);
int			get_num_thread(void);

#endif
