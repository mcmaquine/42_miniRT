/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 21:13:34 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/06 21:13:35 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_sphere(void *obj)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	free(sphere);
}

void	clear_plane(void *obj)
{
	t_plane	*plane;

	plane = (t_plane *)obj;
	free(plane);
}

void	clear_cylinder(void *obj)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)obj;
	free(cylinder);
}
