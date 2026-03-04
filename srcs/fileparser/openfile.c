/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:35:40 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/04 20:24:29 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parser_line(char* line, t_scene *scene_obj);

t_scene*	read_file(char *filename)
{
	int		fd;
	int		status;
	char*	line;
	t_scene	*scene_obj;

	fd = open(filename, O_RDONLY);
	if (fd < 3)
		return (NULL);
	scene_obj = ft_calloc(1, sizeof(t_scene));
	line = get_next_line(fd);
	while (line)
	{
		status = parser_line(line, scene_obj);
		if (!status)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scene_obj);
}

static int	parser_line(char* line, t_scene *scene_obj)
{
	
}
