/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:29:47 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 01:18:21 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_scene(t_scene *scene);
void	free_mlx(void *mlx, void *win, void *img);

void	free_window(t_window *win)
{
	free_scene(win->scene_obj);
	free_mlx(win->mlx, win->win, win->canva.img);
}

/* free_scene

amb_light is alloc?
cam is alloc?
light is alloc?
*/
void	free_scene(t_scene *scene)
{
	int		i;
	t_list	**lst;

	if (!scene)
		return ;
	free_bvh(scene->tree);
	free(scene->amb);
	free(scene->cam);
	ft_lstclear(&(scene->light), free);
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
