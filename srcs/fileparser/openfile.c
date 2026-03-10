/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:35:40 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/09 17:57:01 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parser_line(char* line, t_scene *scene_obj);
static void	parse_obj(char **param, t_scene *scene_obj);

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
		{
			free_scene_obj(&scene_obj);
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (scene_obj);
}

static int	parser_line(char* line, t_scene *scene_obj)
{
	char	**params;
	int		i;

	params = ft_split(line, ' ');
	if (!params)
		return (1);
	parse_obj(params, scene_obj);
	ft_free_split(params);
	i = 0;
}

static void	parse_obj(char	**params, t_scene *scene_obj)
{
	if (!ft_strcmp(params[0], "A"))
		;
	else if (!ft_strcmp(params[0], "C"))
		;
	else if (!ft_strcmp(params[0], "L"))
		;
	else if (!ft_strcmp(params[0], "sp"))
		;
	else if (!ft_strcmp(params[0], "pl"))
		;
	else if (!ft_strcmp(params[0], "cy"))
		;
}
