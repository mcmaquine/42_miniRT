/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/03 13:54:13 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "definitions.h"

typedef struct s_color
{
	double	step_tpcy;
	double	step_r;
	double	step_g;
	double	step_b;
	double	tpcy;
	double	red;
	double	green;
	double	blue;
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
	int			x;
	int			y;
	int			z;
	__uint32_t	color;
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
	double		curr_scale;
	int			pan_x;
	int			pan_y;
} t_window;

typedef struct s_scene_obj
{
	e_obj_type	type;
}	t_scene_obj;

typedef struct s_amb_light
{
	
}	t_amb_light;

#endif