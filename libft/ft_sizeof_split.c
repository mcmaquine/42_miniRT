/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeof_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:44:29 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/09 20:56:55 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
   Counts how many itens has in params, not including NULL element in the end.
*/
size_t	ft_sizeof_split(char **params)
{
	size_t	size;

	if (!params)
		return (0);
	size = 0;
	while (params[size])
		size++;
	return (size);	
}

