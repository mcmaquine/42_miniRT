/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:42:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/05/15 18:02:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const char	*obj_name(t_objs_type obj)
{
	const char	*names[TOTAL] = {
	[OBJ_AMBIENT] = "Ambient lighting",
	[OBJ_CAMERA] = "Camera",
	[OBJ_LIGHT] = "Light",
	[OBJ_SPHERE] = "Sphere",
	[OBJ_PLANE] = "Plane",
	[OBJ_CYLINDER] = "Cylinder",
	};

	return (names[obj]);
}

static const char	*error_msg(t_error_option option)
{
	const char	*msgs[TOTAL_OPTIONS] = {
	[ERR_NO_INFORMATION] = "don`t have all the specific information",
	[ERR_NO_OBJECT] = "missing object declaration in scene file",
	[ERR_NO_PARAM_RATIO] = "missing ratio parameter",
	[ERR_RATIO_OUT_RANGE] = "ratio out of range [0.0, 1.0]",
	[ERR_NO_PARAM_COLOR] = "missing color parameter",
	[ERR_COLOR_OUT_RANGE] = "color value out of range [0, 255]",
	[ERR_NO_PARAM_COORDS] = "missing coordinates parameter",
	[ERR_COORDS_INVALID] = "invalid coordinates value",
	[ERR_NO_PARAM_VEC] = "missing orientation vector parameter",
	[ERR_VEC_OUT_RANGE] = "normalized vector value out of range [-1, 1]",
	[ERR_NO_PARAM_DIAMETER] = "missing diameter parameter",
	[ERR_DIAMETER_NEGATIVE] = "diameter value negative",
	[ERR_NO_PARAM_HEIGHT] = "missing height parameter",
	};

	return (msgs[option]);
}

void	print_error(t_objs_type obj, t_error_option option, int line)
{
	printf("miniRT: %s: %s (line %d)\n", obj_name(obj), error_msg(option), line);
}
