/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:29:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/08 15:46:01 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_window(t_window *win)
{
	if (win->scene_obj)
		free_scene(win->scene_obj);
	free_mlx(win->mlx, win->win, win->canva.img);
}

void	free_scene(t_scene *scene)
{
	int		i;
	t_list	**lst;

	free(scene->amb);
	free(scene->cam);
	free(scene->light);
	i = 0;
	while (i < COUNT)
	{
		lst = &scene->objs[i];
		ft_lstclear(lst, free);
		i++;
	}
	free(scene);
}

void	free_mlx(void *mlx, void *win, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
	if (win)
		mlx_destroy_window(mlx, win);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
}
