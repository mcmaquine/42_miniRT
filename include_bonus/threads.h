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

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

typedef struct s_tile
{
	int				x_start;
	int				y_start;
	int				width;
	int				height;
}	t_tile;

typedef struct s_render_queue
{
	t_tile			*tiles;
	int				num_tiles;
	int				next_tile;
	pthread_mutex_t	lock;
}	t_render_queue;

typedef struct s_thread
{
	t_window		*scene;
	int				id;
	pthread_t		thread_id;
	t_render_queue	*queue;
}	t_thread;

/* thread.c */
t_render_queue	*queue_init(int width, int height, int tile_size);
t_thread		*thread_init(t_window *win, t_render_queue *queue, int num_threads);

/* thread_routine.c */
void			*routine(void *arg);
int				get_num_thread(void);

#endif
