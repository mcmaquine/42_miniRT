/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 20:51:29 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/05 21:43:07 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_scene_obj	**array_objs(t_list *objs[], int n)
{
	t_scene_obj	**array;
	t_list		*lst;
	int			i;

	array = ft_calloc(n, sizeof(t_scene_obj *));
	if (!array)
		return (NULL);
	lst = objs[SPHERE];
	i = -1;
	while (lst)
	{
		array[++i] = (t_scene_obj *)lst->content;
		lst = lst->next;
	}
	lst = objs[CYLINDER];
	while (lst)
	{
		array[++i] = (t_scene_obj *)lst->content;
		lst = lst->next;
	}
	lst = objs[CONE];
	while (lst)
	{
		array[++i] = (t_scene_obj *)lst->content;
		lst = lst->next;
	}
	return (array);
}
