/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/06/22 22:05:37 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define width 1280 // pass to header
#define height 720 // pass to header

static void	start_mlx(t_window *scene);
void render(t_scene *scene);

int	main(int argc, char *argv[])
{
	t_window	scene;

	if (argc != 2)
		return (1); // message given a usage example
	//TODO valid file extension
	//TODO update scene_obj -> *scene_obj in header
	scene = read_file(argv[1]);
	start_mlx(&scene);
	render(&scene);
	mlx_loop(scene->mlx);
}

// move function above to srcs/window/start_window.c

static void	start_mlx(t_window *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, width, height, "miniRT");
	scene.canva->img = mlx_new_image(scene->mlx, width, height);
	scene.canva->addr = mlx_get_data_addr(scene.canva->img, \
&scene.canva.bits_per_pixel, &scene.canva.line_length, &scene.canva.endian);
}

void render(t_window *scene)
{
	int		px;
	int		py;
	char	*ptr;

	ptr = scene.canva->addr;
	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			all_intersections(scene, px, py);
			//calc color pixel;
			ptr++;
			px++;
		}
		py++;
	}
}
