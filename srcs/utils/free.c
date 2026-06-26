//header

#include "minirt.h"

void	free_window(t_window *win)
{
	free_scene(win->scene_obj);
	free_mlx(win->mlx, win->win, win->canva->img);
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
	void	(*ft[COUNT])(void *) = {
	clear_sphere,
	clear_plane,
	clear_cylinder
	};

	i = 0;
	while (i < COUNT)
	{
		lst = &scene->objs[i];
		ft_lstclear(lst, ft[i]);
		i++;
	}
}

void	clear_sphere(void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	free(sphere);
}

void	clear_plane(void *obj)
{
	t_plane	*plane;

	plane = (t_plane *)obj;
	free(plane);
}

void	clear_cylinder(void *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)obj;
	clear_plane(&cylinder.top);
	clear_plane(&cylinder.base);
	free(cylinder);
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