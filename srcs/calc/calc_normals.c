/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:21:31 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/02 18:11:37 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	sphere_calc(t_scene_obj *obj);
static void	plane_calc(t_scene_obj *obj);
static void	cylinder_calc(t_scene_obj *obj);

void	calc_components(t_scene *scene)
{
	static t_objs	map[COUNT] = {
	[SPHERE] = sphere_calc,
	[PLANE] = plane_calc,
	[CYLINDER] = cylinder_calc,
	};
	t_objs			ft;
	t_list			*node;
	int				i;

	scene->cam->orient = vec_normalize(scene->cam->orient);
	i = 0;
	while (i < COUNT)
	{
		node = scene->objs[i];
		while (node)
		{
			ft = map[i];
			ft((t_scene_obj *)node->content);
			node = node->next;
		}
		i++;
	}
}

static void	sphere_calc(t_scene_obj *obj)
{
	t_sphere	*sp;

	sp = (t_sphere *)obj;
	sp->r_sq = sp->diam * sp->diam * 0.25;
}

static void	plane_calc(t_scene_obj *obj)
{
	t_plane	*pl;

	pl = (t_plane *)obj;
	pl->normal = vec_normalize(pl->normal);
}

static void	cylinder_calc(t_scene_obj *obj)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)obj;
	cy->radius = cy->diam * 0.5;
	cy->r_sq = cy->diam * cy->diam * 0.25;
	cy->v_axis = vec_normalize(cy->v_axis);
	cy->height_2 = cy->height / 2;
	cy->top.normal = cy->v_axis;
	cy->base.normal = cy->v_axis;
	cy->top.a_point = vec_add(cy->center, vec_scale(cy->v_axis, cy->height_2));
	cy->base.a_point = vec_sub(cy->center, vec_scale(cy->v_axis, cy->height_2));
	cy->top.color = cy->color;
	cy->base.color = cy->color;
	cy->top.type.base = PLANE;
	cy->base.type.base = PLANE;
}
