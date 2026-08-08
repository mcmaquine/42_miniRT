/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 23:54:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 23:57:32 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_bvh_node	*build_bvh_leaf(t_scene_obj **objs);

t_bvh_node	*build_bvh(t_scene_obj **objs, int n)
{
	static int	(*g_axis_cmp[3])(const void *a, const void *b) = {
		compare_x, compare_y, compare_z
	};
	t_bvh_node	*node;
	t_aabb		box;

	if (n == 1)
		return (build_bvh_leaf(objs));
	box = group_aabb(objs, n);
	qsort(objs, n, sizeof(t_scene_obj *), g_axis_cmp[choose_axis(box)]);
	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->type.base = NODE;
	node->box = box;
	node->left = build_bvh(objs, (n >> 1));
	if (!node->left)
		return (NULL);
	node->right = build_bvh(objs + (n >> 1), (n - (n >> 1)));
	if (!node->right)
	{
		free_bvh(node->left);
		return (NULL);
	}
	return (node);
}

static t_bvh_node	*build_bvh_leaf(t_scene_obj **objs)
{
	t_bvh_node	*node;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->type.base = OBJ;
	node->obj = objs[0];
	node->box = get_aabb(objs[0]);
	return (node);
}

int	choose_axis(t_aabb box)
{
	t_point		ext;

	ext.x = box.max.x - box.min.x;
	ext.y = box.max.y - box.min.y;
	ext.z = box.max.z - box.min.z;
	if (ext.x > ext.y && ext.x > ext.z)
		return (0);
	if (ext.y > ext.x && ext.y > ext.z)
		return (1);
	return (2);
}

void	free_bvh(t_bvh_node *node)
{
	if (!node)
		return ;
	if (node->type.base == NODE)
	{
		if (node->left)
			free_bvh(node->left);
		if (node->right)
			free_bvh(node->right);
	}
	free(node);
}
