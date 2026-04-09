/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:07:53 by mmaquine          #+#    #+#             */
/*   Updated: 2026/04/07 17:35:30 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H
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

typedef enum e_obj_type
{
	LIGHT,
	CAMERA,
	AMBIENT_LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	COUNT
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

#endif
