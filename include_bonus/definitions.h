/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:07:53 by mmaquine          #+#    #+#             */
/*   Updated: 2026/07/04 17:42:10 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H
# define REAL double
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define ESC 65307
# define MOUSE_SCR_UP 4
# define MOUSE_SCR_DOWN 5
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_O 111
# define KEY_L 108
# define KEY_K 107
# define WIDTH 1000
# define HEIGHT 1000
# define EPSILON 1e-4

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	COUNT,
	LIGHT,
	CAMERA,
	AMBIENT_LIGHT
}	t_obj_type;

enum	e_identifier
{
	A,
	C,
	L,
	sp,
	pl,
	cy
};

typedef enum e_objs_type
{
	OBJ_AMBIENT,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	TOTAL
}	t_objs_type;

typedef enum e_error_option
{
	ERR_NO_INFORMATION,
	ERR_NO_OBJECT,
	ERR_NO_UNIQUE,
	ERR_NO_PARAM_RATIO,
	ERR_NO_PARAM_COLOR,
	ERR_NO_PARAM_COORDS,
	ERR_NO_PARAM_VEC,
	ERR_NO_PARAM_DIAMETER,
	ERR_NO_PARAM_HEIGHT,
	ERR_OUT_RANGE_FOV,
	ERR_OUT_RANGE_RATIO,
	ERR_OUT_RANGE_BRIGHT,
	ERR_OUT_RANGE_COLOR,
	ERR_OUT_RANGE_VEC,
	ERR_COORDS_INVALID,
	ERR_DIAMETER_NEGATIVE,
	TOTAL_OPTIONS
}	t_error_option;

#endif
