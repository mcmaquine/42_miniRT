/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/07 00:00:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int argc, char *argv[])
{
	t_window		scene;
	t_render_queue	*queue;
	t_thread		*threads;
	int				num_threads;
	int				i;

	if (argc != 2)
		return (1); // message given a usage example
	//TODO valid file extension
	scene.scene_obj = read_file(argv[1]);
	calc_components(scene.scene_obj); // calculate normals
	start_window(&scene, WIDTH, HEIGHT);
	num_threads = get_num_thread();
	queue = queue_init(WIDTH, HEIGHT, TILE_SIZE);
	threads = thread_init(&scene, queue, num_threads);
	i = 0;
	long start = get_current_time();
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
	long end = get_current_time();
	if (end - start > 1000)
		printf("end calcs in %ld.%ld\n", ((end - start) / 1000), ((end - start) - ((end - start) / 1000 * 1000)));
	else
		printf("end calcs in %ld\n", end - start);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.canva.img, 0, 0);
	mlx_loop(scene.mlx);
	pthread_mutex_destroy(&queue->lock);
	free(queue->tiles);
	free(queue);
	free(threads);
	return (0);
}
