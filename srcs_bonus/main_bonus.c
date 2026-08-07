/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 00:09:26 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	init_scene(t_window *scene, char *filename);
static void	print_render_time(long start, long end);
static void	render_scene(t_window *scene, t_thread *threads, int num_threads);
static void	free_all(t_window *scene, t_render_queue *queue, t_thread *threads);

int	main(int argc, char *argv[])
{
	t_window		scene;
	t_render_queue	*queue;
	t_thread		*threads;
	int				num_threads;

	if (argc != 2)
		return (1);
	init_scene(&scene, argv[1]);
	num_threads = get_num_thread();
	queue = queue_init(WIDTH, HEIGHT, TILE_SIZE);
	threads = thread_init(&scene, queue, num_threads);
	render_scene(&scene, threads, num_threads);
	mlx_loop(scene.mlx);
	free_all(&scene, queue, threads);
	return (0);
}

static void	init_scene(t_window *scene, char *filename)
{
	scene->scene_obj = read_file(filename);
	calc_components(scene->scene_obj);
	init_bvh(scene->scene_obj);
	start_window(scene, WIDTH, HEIGHT);
}

static void	print_render_time(long start, long end)
{
	long	elapsed;

	elapsed = end - start;
	if (elapsed > 1000)
		printf("end calcs in %ld.%ld\n", (elapsed / 1000),
			(elapsed - (elapsed / 1000 * 1000)));
	else
		printf("end calcs in %ld\n", elapsed);
}

static void	render_scene(t_window *scene, t_thread *threads, int num_threads)
{
	int		i;
	long	start;
	long	end;

	i = 0;
	start = get_current_time();
	while (i < num_threads)
	{
		pthread_create(&threads[i].thread_id, NULL, routine, &threads[i]);
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		pthread_join(threads[i].thread_id, NULL);
		i++;
	}
	end = get_current_time();
	print_render_time(start, end);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canva.img, 0, 0);
}

static void	free_all(t_window *scene, t_render_queue *queue, t_thread *threads)
{
	pthread_mutex_destroy(&queue->lock);
	free(queue->tiles);
	free(queue);
	free(threads);
	free_window(scene);
}
