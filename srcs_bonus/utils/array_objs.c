/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 20:51:29 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 00:14:52 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	fill_array(t_scene_obj **array, t_list *lst, int i)
{
	while (lst)
	{
		array[i] = (t_scene_obj *)lst->content;
		i++;
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
	i = 0;
	i = fill_array(array, objs[SPHERE], i);
	i = fill_array(array, objs[CYLINDER], i);
	fill_array(array, objs[CONE], i);
	return (array);
}
