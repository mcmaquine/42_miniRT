/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/14 11:13:13 by gabrgarc         ###   ########.fr       */
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

//file struct, must be changed
typedef struct s_data
{
	int				abscissa;
	int				ordinate;
	int				**coord;
	unsigned int	**color;
}	t_data;

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

typedef struct s_window
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_canva		canva;
	t_data		data;
	t_list		*scene_obj;
}	t_window;

typedef struct s_scene_obj
{
	t_obj_type	base;
}	t_scene_obj;

typedef struct s_amb_light
{
	t_scene_obj	type;
	double		light_rate;
	t_color		color;
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
	double		bright_rate;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_scene_obj	type;
	t_point		center;
	t_color		color;
	double		diam;
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
	t_list		*objs[COUNT];
}	t_scene;

#endif
