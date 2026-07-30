/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/07/01 09:00:40 by mmaquine         ###   ########.fr       */
=======
/*   Updated: 2026/07/04 17:37:37 by gabrgarc         ###   ########.fr       */
>>>>>>> bonus/threads
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render(t_window *scene);
static int pixel_color(t_color color);

int	main(int argc, char *argv[])
{
	t_window	scene;

	if (argc != 2)
		return (1); // message given a usage example
	//TODO valid file extension
	//TODO update scene_obj -> *scene_obj in header
	scene.scene_obj = read_file(argv[1]);
	if (!scene.scene_obj)
		return(1);
	calc_components(scene.scene_obj); // calculate normals
	start_window(&scene, WIDTH, HEIGHT);
	render(&scene);
	mlx_loop(scene.mlx);
	return (0);
}

#include <sys/time.h>
long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void render(t_window *scene)
{
	int		px;
	int		py;
	int		*ptr;
	t_hit	hit;
	t_color	color;
	t_ray	ray;

	ptr = (int *)scene->canva.addr;
	py = 0;
	long start = get_current_time();
	while (py < HEIGHT)
	{
		px = 0;
		while (px < WIDTH)
		{
			ray = generate_ray(scene, px, py);
			hit = all_intersections(scene, ray);
			color = calculate_illumination(scene, hit);
			*ptr = pixel_color(color);
			ptr++;
			px++;
		}
		py++;
	}
	printf("end calcs in %ld\n", get_current_time() - start);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canva.img, 0, 0);
}

static int pixel_color(t_color color)
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
