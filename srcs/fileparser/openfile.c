/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:35:40 by mmaquine          #+#    #+#             */
/*   Updated: 2026/08/08 11:55:22 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		process_line(int fd, t_scene *scene_obj);
static int		parser_line(char *line, t_scene *scene_obj);
static int		parse_obj(char **param, t_scene *scene_obj);
static t_scene	*validate_unique_obj(t_scene **scene_obj);

t_scene	*read_file(char *filename)
{
	int		fd;
	t_scene	*scene_obj;

	if (!valid_extension(filename, ".rt"))
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("miniRT: %s: No such file or directory\n", filename);
		return (NULL);
	}
	scene_obj = ft_calloc(1, sizeof(t_scene));
	if (process_line(fd, scene_obj))
		return (NULL);
	return (validate_unique_obj(&scene_obj));
}

int	process_line(int fd, t_scene *scene_obj)
{
	char	*line;
	int		status;

	scene_obj->line = 0;
	line = get_next_line(fd);
	while (line)
	{
		scene_obj->line++;
		status = parser_line(line, scene_obj);
		if (status)
		{
			free_scene_obj(&scene_obj);
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

static int	parser_line(char *line, t_scene *scene_obj)
{
	char	**params;
	int		i;

	params = ft_strsplit_any(line, "\t\n\v\f\r ");
	if (!params)
		return (1);
	if (!params[0] || params[0][0] == '#')
	{
		ft_free_split(params);
		return (0);
	}
	i = parse_obj(params, scene_obj);
	ft_free_split(params);
	return (i);
}

static int	parse_obj(char **params, t_scene *scene_obj)
{
	if (!ft_strcmp(params[0], "A"))
		return (amb_light_parser(params, scene_obj));
	if (!ft_strcmp(params[0], "C"))
		return (cam_parser(params, scene_obj));
	if (!ft_strcmp(params[0], "L"))
		return (light_parser(params, scene_obj));
	if (!ft_strcmp(params[0], "sp"))
		return (sphere_parser(params, scene_obj));
	if (!ft_strcmp(params[0], "pl"))
		return (plane_parser(params, scene_obj));
	if (!ft_strcmp(params[0], "cy"))
		return (cilinder_parser(params, scene_obj));
	return (print_error(OBJ_SCENE, ERR_UNKNOWN_OBJECT, scene_obj->line));
}

static t_scene	*validate_unique_obj(t_scene **scene_obj)
{
	if (!(*scene_obj)->amb)
		print_error(OBJ_AMBIENT, ERR_NO_OBJECT, (*scene_obj)->line);
	else if (!(*scene_obj)->cam)
		print_error(OBJ_CAMERA, ERR_NO_OBJECT, (*scene_obj)->line);
	else if (!(*scene_obj)->light)
		print_error(OBJ_LIGHT, ERR_NO_OBJECT, (*scene_obj)->line);
	else
		return (*scene_obj);
	free_scene_obj(scene_obj);
	return (NULL);
}
