/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:44:16 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/07 00:00:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	count_tiles(int width, int height, int tile_size)
{
	int	cols;
	int	rows;

	cols = (width + tile_size - 1) / tile_size;
	rows = (height + tile_size - 1) / tile_size;
	return (cols * rows);
}

static void	fill_tiles(t_tile *tiles, int width, int height, int tile_size)
{
	int	cols;
	int	num_tiles;
	int	i;

	cols = (width + tile_size - 1) / tile_size;
	num_tiles = count_tiles(width, height, tile_size);
	i = 0;
	while (i < num_tiles)
	{
		tiles[i].x_start = (i % cols) * tile_size;
		tiles[i].y_start = (i / cols) * tile_size;
		if (tiles[i].x_start + tile_size < width)
			tiles[i].width = tile_size;
		else
			tiles[i].width = width - tiles[i].x_start;
		if (tiles[i].y_start + tile_size < height)
			tiles[i].height = tile_size;
		else
			tiles[i].height = height - tiles[i].y_start;
		i++;
	}
}

t_render_queue	*queue_init(int width, int height, int tile_size)
{
	t_render_queue	*queue;

	queue = ft_calloc(1, sizeof(t_render_queue));
	queue->num_tiles = count_tiles(width, height, tile_size);
	queue->tiles = ft_calloc(queue->num_tiles, sizeof(t_tile));
	fill_tiles(queue->tiles, width, height, tile_size);
	queue->next_tile = 0;
	pthread_mutex_init(&queue->lock, NULL);
	return (queue);
}

t_thread	*thread_init(t_window *win, t_render_queue *queue, int num_threads)
{
	t_thread	*threads;
	int			i;

	threads = ft_calloc(num_threads, sizeof(t_thread));
	i = 0;
	while (i < num_threads)
	{
		threads[i].scene = win;
		threads[i].id = i + 1;
		threads[i].queue = queue;
		i++;
	}
	return (threads);
}
