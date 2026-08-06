/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 00:23:39 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/07 00:23:40 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_list	*list_of_objs(t_list *objs[])
{
	t_list	*head;
	t_list	*last;

	if (objs[0])
		head = objs[0];
	else
		return (objs[2]);
	last = ft_lstlast(head);
	if (objs[2])
		last->next = objs[2];
	return (head);
}
