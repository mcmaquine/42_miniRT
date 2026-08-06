/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 20:47:39 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/05 21:09:29 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	count_objs(t_list *objs[])
{
	int	i;

	i = ft_lstsize(objs[SPHERE]);
	i += ft_lstsize(objs[CYLINDER]);
	i += ft_lstsize(objs[CONE]);
	return (i);
}
