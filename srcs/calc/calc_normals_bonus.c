/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normals_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 00:00:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/01 00:00:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_calc(t_scene_obj *obj);
static void	plane_calc(t_scene_obj *obj);
static void	cylinder_calc(t_scene_obj *obj);

void	calc_components(t_scene *scene)
{
	t_objs	map[COUNT];
	t_list	*node;
	int		i;

	map[SPHERE] = sphere_calc;
	map[PLANE] = plane_calc;
	map[CYLINDER] = cylinder_calc;
	scene->cam->orient = vec_normalize(scene->cam->orient);
	i = 0;
	while (i < COUNT)
	{
		node = scene->objs[i];
		while (node)
		{
			map[i]((t_scene_obj *)node->content);
			node = node->next;
		}
		i++;
	}
}

static void	sphere_calc(t_scene_obj *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	sphere->r_sq = sphere->diam * sphere->diam * 0.25;
}

static void	plane_calc(t_scene_obj *obj)
{
	t_plane	*plane;

	plane = (t_plane *)obj;
	plane->normal = vec_normalize(plane->normal);
}

static void	cylinder_calc(t_scene_obj *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)obj;
	cylinder->radius = cylinder->diam * 0.5;
	cylinder->r_sq = cylinder->diam * cylinder->diam * 0.25;
	cylinder->v_axis = vec_normalize(cylinder->v_axis);
	cylinder->height_2 = cylinder->height / 2;
	cylinder->top.normal = cylinder->v_axis;
	cylinder->base.normal = cylinder->v_axis;
	cylinder->top.a_point = vec_add(cylinder->center,
			vec_scale(cylinder->v_axis, cylinder->height_2));
	cylinder->base.a_point = vec_sub(cylinder->center,
			vec_scale(cylinder->v_axis, cylinder->height_2));
	cylinder->top.color = cylinder->color;
	cylinder->base.color = cylinder->color;
	cylinder->top.material = cylinder->material;
	cylinder->base.material = cylinder->material;
	cylinder->top.type.base = PLANE;
	cylinder->base.type.base = PLANE;
}
