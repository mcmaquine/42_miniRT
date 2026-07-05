/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:48:54 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/07/04 16:44:18 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void render(t_window *scene, t_thread *thread);
static inline int pixel_color(t_color color);

void	*routine(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	render(thread->scene, thread);
	return (NULL);
}

void render(t_window *scene, t_thread *thread)
{
	int		px;
	int		py;
	t_hit	hit;
	t_color	color;
	t_ray	ray;

	py = 0;
	while (py < thread->height)
	{
		px = 0;
		while (px < thread->width)
		{
			ray = generate_ray(scene, px, thread->y_start + py);
			hit = all_intersections(scene, ray);
			color = calculate_illumination(scene, hit);
			*thread->addr = pixel_color(color);
			thread->addr++;
			px++;
		}
		py++;
	}
}

static inline int pixel_color(t_color color)
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
