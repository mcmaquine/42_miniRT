/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytracer_bonus.h"

static int	pixel_color(t_color color)
{
	int	transparency;
	int	red;
	int	green;
	int	blue;

	transparency = color.tpcy;
	red = (int)(color.red * 255.0);
	green = (int)(color.green * 255.0);
	blue = (int)(color.blue * 255.0);
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

static void	render_bonus(t_window *scene)
{
	int		x;
	int		y;
	int		*pixel;
	t_ray	ray;

	pixel = (int *)scene->canva.addr;
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = generate_ray(scene, x, y);
			*pixel = pixel_color(trace_color_bonus(scene, ray,
						MAX_REFLECTION_DEPTH));
			pixel++;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canva.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_window	scene;

	if (argc != 2)
		return (1);
	scene.scene_obj = read_file(argv[1]);
	if (!scene.scene_obj)
		return (1);
	calc_components(scene.scene_obj);
	start_window(&scene, WIDTH, HEIGHT);
	render_bonus(&scene);
	mlx_loop(scene.mlx);
	return (0);
}
