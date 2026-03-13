/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:41:36 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/13 10:43:02 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	tracer(t_cam *cam, t_window *win, int px, int py)
{
	t_point	forward;
	t_point	world_up;
	t_point	right;
	t_point	up;

	forward = vec_normalize(cam->orient);
	world_up = fill_point(0, 1, 0);
	right = vec_normalize(vec_cross(world_up, forward));
	up = vec_normalize(vec_cross(forward, right));
}
