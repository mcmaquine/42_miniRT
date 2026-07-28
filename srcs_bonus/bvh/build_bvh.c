#include "minirt_bonus.h"

t_bvh_node	*build_bvh(t_scene_obj **objs, int n)
{
	t_bvh_node	*node;
	t_aabb		box;
	static int	(*ft[3])(const void *a, const void *b) = {
		compare_x,
		compare_y,
		compare_z
	};

	if (n == 1)
	{
		node = ft_calloc(1, sizeof(t_bvh_node));
		if (!node)
			return (NULL);
		node->base = OBJ;
		node->obj = objs[0];
		node->box = get_aabb(objs[0]);
		return (node);
	}
	box = group_aabb(objs, n);
	qsort(objs, n, sizeof(t_scene_obj *), ft[choose_axis(box)]);
	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->base = NODE;
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
	if (node->type == OBJ)
		free(node);
	else
	{
		if (node->left)
			free_bvh(node->left);
		if (node->right)
			free_bvh(node->right);
	}
}
