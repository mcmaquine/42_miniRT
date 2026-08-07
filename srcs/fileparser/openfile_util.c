/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 21:14:01 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/08/07 00:41:57 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	valid_extension(char *file, char *extension)
{
	size_t	len_file;
	size_t	len_ext;
	char	*ptr_dot;

	if (!file || !extension)
		return (0);
	len_file = ft_strlen(file);
	len_ext = ft_strlen(extension);
	if (len_ext == 0 || len_ext > len_file)
		return (0);
	ptr_dot = &file[len_file - len_ext];
	while (*extension && *ptr_dot == *extension)
	{
		ptr_dot++;
		extension++;
	}
	if (*ptr_dot)
	{
		ft_printf("Error\nminiRT: file: Invalid extension\n");
		return (0);
	}
	return (1);
}
