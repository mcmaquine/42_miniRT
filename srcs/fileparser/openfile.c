/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:35:40 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/12 16:42:10 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		parser_line(char* line, t_scene *scene_obj);
static int		parse_obj(char **param, t_scene *scene_obj);
static t_scene	*validate_unique_obj(t_scene **scene_obj);

t_scene*	read_file(char *filename)
{
	int		fd;
	int		status;
	char*	line;
	t_scene	*scene_obj;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	scene_obj = ft_calloc(1, sizeof(t_scene));
	line = get_next_line(fd);
	while (line)
	{
		status = parser_line(line, scene_obj);
		if (status)
		{
			free_scene_obj(&scene_obj);
			free(line);
			close (fd);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_unique_obj(&scene_obj));
}

static int	parser_line(char* line, t_scene *scene_obj)
{
	char	**params;
	int		i;

	params = ft_split(line, ' ');
	if (!params)
		return (1);
	if (ft_sizeof_split(params) == 1)
	{
		ft_free_split(params);
		return (0);
	}
	i = parse_obj(params, scene_obj);
	ft_free_split(params);
	return (i);
}

static int	parse_obj(char	**params, t_scene *scene_obj)
{
	if (!ft_strcmp(params[0], "A"))
		return (amb_light_parser(params, scene_obj));
	else if (!ft_strcmp(params[0], "C"))
		return (cam_parser(params, scene_obj));
	else if (!ft_strcmp(params[0], "L"))
		return (light_parser(params, scene_obj));
	else if (!ft_strcmp(params[0], "sp"))
		return (sphere_parser(params, scene_obj));
	else if (!ft_strcmp(params[0], "pl"))
		return (plane_parser(params, scene_obj));
	else if (!ft_strcmp(params[0], "cy"))
		return (cilinder_parser(params, scene_obj));
	return (0);
}

static t_scene	*validate_unique_obj(t_scene **scene_obj)
{
	if (!(*scene_obj)->amb || !(*scene_obj)->cam || !(*scene_obj)->light )
	{
		free_scene_obj(scene_obj);
		return (NULL);
	}
	else
		return (*scene_obj);
}