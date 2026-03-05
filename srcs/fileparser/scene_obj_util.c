/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:24:04 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/05 13:31:31 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Free all memory allocated for t_scene_obj
*/
void	free_scene_obj(t_scene **scene_obj)
{
	if (!(*scene_obj))
		return ;
	free((*scene_obj)->amb);
	free((*scene_obj)->cam);
	free((*scene_obj)->light);
	ft_lstclear(&((*scene_obj)->objs), free);
	free(*scene_obj);
	*scene_obj = NULL;
}
