/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/01 18:59:46 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "definitions.h"
# include <ctype.h>
# include "libft.h"

typedef struct s_color
{
	int	tpcy;
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_canva
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_canva;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_matrix
{
	int		row;
	int		col;
	double	**a;
}	t_matrix;

typedef struct s_scene_obj
{
	t_obj_type	type;
}	t_scene_obj;

typedef struct s_amb_light
{
	t_obj_type	type;
	double		light_rate;
	t_color		color;
}	t_amb_light;

typedef struct s_cam
{
	t_obj_type	type;
	t_point		point;
	t_point		orient;
	double		fov;
}	t_cam;

typedef struct s_light
{
	t_obj_type	type;
	t_point		coord;
	double		bright_rate;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_obj_type	type;
	t_point		center;
	t_color		color;
	double		diam;
}	t_sphere;

typedef struct s_plane
{
	t_obj_type	type;
	t_point		a_point;
	t_point		normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_obj_type	type;
	t_point		center;
	t_point		v_axis;
	double		diam;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_scene
{
	t_amb_light	*amb;
	t_cam		*cam;
	t_light		*light;
	t_list		*objs;
}	t_scene;

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

typedef struct s_window
{
	t_scene		scene_obj;
	t_canva		canva;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
}	t_window;

#endif