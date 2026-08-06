/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:48:54 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 01:01:43 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void		render_tile(t_window *scene, t_tile *tile);
static inline int	pixel_color(t_color color);
static int	next_tile(t_render_queue *queue);

void	*routine(void *arg)
{
	t_thread	*thread;
	int			idx;

	thread = (t_thread *)arg;
	idx = next_tile(thread->queue);
	while (idx != -1)
	{
		render_tile(thread->scene, &thread->queue->tiles[idx]);
		idx = next_tile(thread->queue);
	}
	return (NULL);
}

static int	next_tile(t_render_queue *queue)
{
	int	idx;

	pthread_mutex_lock(&queue->lock);
	if (queue->next_tile < queue->num_tiles)
		idx = queue->next_tile++;
	else
		idx = -1;
	pthread_mutex_unlock(&queue->lock);
	return (idx);
}

void	render_tile(t_window *scene, t_tile *tile)
{
	int		px;
	int		py;
	int		*addr;
	t_color	color;
	t_ray	ray;

	py = 0;
	while (py < tile->height)
	{
		addr = (int *)(scene->canva.addr
				+ (scene->canva.line_length * (tile->y_start + py))
				+ (tile->x_start * sizeof(int)));
		px = 0;
		while (px < tile->width)
		{
			ray = generate_ray(scene, tile->x_start + px, tile->y_start + py);
			color = trace_color_bonus(scene, ray, MAX_REFLECTION_DEPTH);
			addr[px] = pixel_color(color);
			px++;
		}
		py++;
	}
}

static inline int	pixel_color(t_color color)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = color.tpcy;
	r = (int)(color.red * 255.0f);
	g = (int)(color.green * 255.0f);
	b = (int)(color.blue * 255.0f);
	return (t << 24 | r << 16 | g << 8 | b);
}
