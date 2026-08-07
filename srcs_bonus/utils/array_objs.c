/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 20:51:29 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 01:17:09 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	add_objs(t_scene_obj **array, t_list *lst, int i)
{
	while (lst)
	{
		array[++i] = (t_scene_obj *)lst->content;
		lst = lst->next;
	}
	return (i);
}

t_scene_obj	**array_objs(t_list *objs[], int n)
{
	t_scene_obj	**array;
	int			i;

	array = ft_calloc(n, sizeof(t_scene_obj *));
	if (!array)
		return (NULL);
	i = -1;
	i = add_objs(array, objs[SPHERE], i);
	i = add_objs(array, objs[CYLINDER], i);
	i = add_objs(array, objs[CONE], i);
	return (array);
}
