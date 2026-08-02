/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:55 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/02 18:37:01 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		render(t_window *scene);
static int	pixel_color(t_color color);

/* TODO error message when there are two parameters */
int	main(int argc, char *argv[])
{
	t_window	scene;

	if (argc != 2)
		return (1);
	scene.scene_obj = read_file(argv[1]);
	if (!scene.scene_obj)
		return (1);
	calc_components(scene.scene_obj);
	start_window(&scene, WIDTH, HEIGHT);
	render(&scene);
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
	t_ray	ray;

	ptr = (int *)scene->canva.addr;
	py = 0;
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
