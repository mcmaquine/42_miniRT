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

#endif
