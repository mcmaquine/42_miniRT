/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/04 18:55:27 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "definitions.h"
# include <ctype.h>
# include "libft.h"

typedef struct s_bvh_node	t_bvh_node;

typedef struct s_color
{
	double	tpcy;
	double	red;
	double	green;
	double	blue;
}	t_color;

typedef struct s_canva
{
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}	t_canva;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_matrix
{
	double	**a;
	int		row;
	int		col;
}	t_matrix;

typedef struct s_scene_obj
{
	t_obj_type	base;
}	t_scene_obj;

typedef enum e_pattern
{
	PATTERN_NONE,
	PATTERN_CHECKER
}	t_pattern;

typedef struct s_material
{
	t_pattern	pattern;
	t_color		checker_color;
	double		checker_scale;
	char		*bump_path;
	double		bump_strength;
	double		reflection;
}	t_material;

typedef struct s_amb_light
{
	t_scene_obj		type;
	t_color			color;
	double			light_rate;
}	t_amb_light;

typedef struct s_cam
{
	t_scene_obj	type;
	t_point		point;
	t_point		orient;
	double		fov;
}	t_cam;

typedef struct s_light
{
	t_scene_obj	type;
	t_point		coord;
	t_color		color;
	double		bright_rate;
}	t_light;

typedef struct s_sphere
{
	t_scene_obj	type;
	t_point		center;
	t_color		color;
	t_material	material;
	double		diam;
	double		r_sq;
}	t_sphere;

typedef struct s_plane
{
	t_scene_obj	type;
	t_point		a_point;
	t_point		normal;
	t_color		color;
	t_material	material;
}	t_plane;

typedef struct s_cylinder
{
	t_scene_obj	type;
	t_plane		top;
	t_plane		base;
	t_point		center;
	t_point		v_axis;
	t_color		color;
	t_material	material;
	double		diam;
	double		height;
	double		height_2;
	double		radius;
	double		r_sq;
}	t_cylinder;

typedef struct s_cone
{
	t_scene_obj	type;
	t_plane		base;
	t_point		vertex;
	t_point		v_axis;
	t_color		color;
	t_material	material;
	double		theta;
	double		height;
	double		radius;
	double		tan2;
}	t_cone;

typedef struct s_scene
{
	t_amb_light	*amb;
	t_cam		*cam;
	t_list		*light;
	t_list		*objs[COUNT];
	t_bvh_node	*tree;
}	t_scene;

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

typedef struct s_hit
{
	double		t;
	t_point		point;
	t_point		normal;
	t_color		color;
	t_scene_obj	*obj;
	t_point		view_origin;
}	t_hit;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_canva		canva;
	t_scene		*scene_obj;
	int			width;
	int			height;
}	t_window;

#endif
