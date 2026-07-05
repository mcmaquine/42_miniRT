/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 17:34:30 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int argc, char *argv[])
{
	t_window	scene;
	t_thread	*threads;
	int			num_threads;
	int			i;

	if (argc != 2)
		return (1); // message given a usage example
	//TODO valid file extension
	scene.scene_obj = read_file(argv[1]);
	calc_components(scene.scene_obj); // calculate normals
	start_window(&scene, WIDTH, HEIGHT);
	num_threads = get_num_thread();
	threads = thread_init(&scene, WIDTH, HEIGHT, num_threads);
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
	printf("end calcs in %ld\n", get_current_time() - start);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.canva.img, 0, 0);
	mlx_loop(scene.mlx);
	free(threads);
	return (0);
}
