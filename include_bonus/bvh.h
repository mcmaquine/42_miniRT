/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 21:48:07 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/05 21:49:53 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "structs.h"

typedef struct	s_aabb
{
	t_point	min;
	t_point	max;
}	t_aabb;

typedef enum	e_bvh_type
{
	NODE,
	OBJ
}	t_bvh_type;

typedef struct	s_bvh_obj
{
	t_bvh_type	base;
}	t_bvh_obj;

typedef struct	s_bvh_node
{
	t_bvh_obj			type;
	t_aabb				box;
	t_scene_obj			*obj;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
}	t_bvh_node;


t_aabb	cone_aabb(t_cone *cone);
t_aabb	sphere_aabb(t_sphere *sphere);
t_bvh_node	*build_bvh(t_scene_obj **objs, int n);
int	compare_x(const void *a, const void *b);
int	compare_y(const void *a, const void *b);
int	compare_z(const void *a, const void *b);
t_aabb	cylinder_aabb(t_cylinder *cylinder);
t_aabb	get_aabb(t_scene_obj *obj);
t_aabb	group_aabb(t_scene_obj **objs, int n);
int	hit_box(t_ray ray, t_aabb box);
t_hit	hit_bvh(t_bvh_node *node, t_ray ray);
void	init_bvh(t_scene *scene);
t_hit	intersect_bvh(t_window *win, t_ray ray);
int	choose_axis(t_aabb box);
void	free_bvh(t_bvh_node *node);

#endif
