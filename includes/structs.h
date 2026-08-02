/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/02 17:36:08 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "definitions.h"
# include <ctype.h>
# include "libft.h"

typedef struct s_color
{
	REAL	tpcy;
	REAL	red;
	REAL	green;
	REAL	blue;
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
	REAL	x;
	REAL	y;
	REAL	z;
}	t_point;

typedef struct s_matrix
{
	REAL	**a;
	int		row;
	int		col;
}	t_matrix;

typedef struct s_scene_obj
{
	t_obj_type	base;
}	t_scene_obj;

typedef struct s_amb_light
{
	t_scene_obj		type;
	t_color			color;
	REAL			light_rate;
}	t_amb_light;

typedef struct s_cam
{
	t_scene_obj	type;
	t_point		point;
	t_point		orient;
	REAL		fov;
}	t_cam;

typedef struct s_light
{
	t_scene_obj	type;
	t_point		coord;
	t_color		color;
	REAL		bright_rate;
}	t_light;

typedef struct s_sphere
{
	t_scene_obj	type;
	t_point		center;
	t_color		color;
	REAL		diam;
	REAL		r_sq;
}	t_sphere;

typedef struct s_plane
{
	t_scene_obj	type;
	t_point		a_point;
	t_point		normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_scene_obj	type;
	t_plane		top;
	t_plane		base;
	t_point		center;
	t_point		v_axis;
	t_color		color;
	REAL		diam;
	REAL		height;
	REAL		height_2;
	REAL		radius;
	REAL		r_sq;
}	t_cylinder;

typedef struct s_scene
{
	t_amb_light	*amb;
	t_cam		*cam;
	t_light		*light;
	t_list		*objs[COUNT];
}	t_scene;

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

typedef struct s_hit
{
	REAL		t;
	t_point		point;
	t_point		normal;
	t_color		color;
	t_scene_obj	*obj;
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
