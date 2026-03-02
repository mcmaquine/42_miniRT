/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:04:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/02 14:06:01 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define ESC 65307

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
	t_matrix	*current_tf;
	double		curr_scale;
	int			pan_x;
	int			pan_y;
} t_window;
#endif