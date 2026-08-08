/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:42:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 01:14:56 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static const char	*obj_name(t_objs_type obj)
{
	const char	*names[TOTAL] = {
	[OBJ_AMBIENT] = "Ambient lighting",
	[OBJ_CAMERA] = "Camera",
	[OBJ_LIGHT] = "Light",
	[OBJ_SPHERE] = "Sphere",
	[OBJ_PLANE] = "Plane",
	[OBJ_CYLINDER] = "Cylinder",
	[OBJ_CONE] = "Cone",
	[OBJ_SCENE] = "Scene",
	};

	return (names[obj]);
}

static const char	*error_msg(t_error_option option)
{
	const char	*msgs[TOTAL_OPTIONS] = {
	[ERR_NO_INFORMATION] = "don`t have all the specific information",
	[ERR_NO_OBJECT] = "missing object declaration in scene file",
	[ERR_NO_UNIQUE] = "not a unique object in scene",
	[ERR_NO_PARAM_RATIO] = "missing ratio parameter",
	[ERR_NO_PARAM_COLOR] = "missing color parameter",
	[ERR_NO_PARAM_COORDS] = "missing coordinates parameter",
	[ERR_NO_PARAM_VEC] = "missing orientation vector parameter",
	[ERR_NO_PARAM_DIAMETER] = "missing diameter parameter",
	[ERR_NO_PARAM_HEIGHT] = "missing height parameter",
	[ERR_OUT_RANGE_FOV] = "fov out of range [0, 180]",
	[ERR_OUT_RANGE_RATIO] = "ratio out of range [0.0, 1.0]",
	[ERR_OUT_RANGE_BRIGHT] = "brightness out of range [0.0,1.0]",
	[ERR_OUT_RANGE_COLOR] = "color value out of range [0-255]",
	[ERR_OUT_RANGE_ANGLE] = "angle out of range (1, 89)",
	[ERR_OUT_RANGE_VEC] = "normalized vector value out of range [-1, 1]",
	[ERR_COORDS_INVALID] = "invalid coordinates value",
	[ERR_DIAMETER_NEGATIVE] = "diameter value negative",
	[ERR_HEIGHT_NEGATIVE] = "height value negative",
	[ERR_UNKNOWN_OBJECT] = "unknown object declaration in scene file",
	};

	return (msgs[option]);
}

void	print_error(t_objs_type obj, t_error_option option, int line)
{
	ft_putstr_fd("Error\n", 1);
	printf("miniRT: %s: %s (line %d)\n", obj_name(obj), error_msg(option),
		line);
}
