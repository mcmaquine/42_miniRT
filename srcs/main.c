/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/08 15:53:09 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		render(t_window *scene);
static int	pixel_color(t_color color);

int	main(int argc, char *argv[])
{
	t_window	scene;

	scene = (t_window){0};
	if (argc > 2)
	{
		ft_printf("Error\nminiRT: params: too many arguments\n");
		return (1);
	}
	if (start_window(&scene, WIDTH, HEIGHT))
	{
		free_window(&scene);
		return (1);
	}
	if (argc == 2)
	{
		scene.scene_obj = read_file(argv[1]);
		if (!scene.scene_obj)
			return (1);
		calc_components(scene.scene_obj);
		render(&scene);
	}
	mlx_loop(scene.mlx);
	return (0);
}

void	render(t_window *scene)
{
	int		px;
	int		py;
	int		*ptr;
	t_hit	hit;
	t_color	color;

	ptr = (int *)scene->canva.addr;
	py = 0;
	while (py < HEIGHT)
	{
		px = 0;
		while (px < WIDTH)
		{
			hit = all_intersections(scene, generate_ray(scene, px, py));
			color = calculate_illumination(scene, hit);
			*ptr = pixel_color(color);
			ptr++;
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->canva.img, 0, 0);
}

static int	pixel_color(t_color color)
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
