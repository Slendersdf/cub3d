/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:53:15 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:24 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/*Verifies we're currently in the map part of file or not.*/
static int	handle_map_line(char *line, t_map *map)
{
	if (!check_all_elements_loaded(map))
		return (0);
	return (parse_map_line(line, map));
}

/*Calls appropriate function whether line is map, tex, col or empty/other.*/
int	process_line(char *line, int type, t_map *map)
{
	if (type == 0)
		return (handle_empty_line(map));
	if (type == 9)
		return (handle_map_line(line, map));
	else if (map->parsing_map)
		return (error_msg("Map must be the last element"));
	if (type >= 1 && type <= 6)
	{
		if (type == 1)
			return (parse_texture(line, &map->textures.no));
		if (type == 2)
			return (parse_texture(line, &map->textures.so));
		if (type == 3)
			return (parse_texture(line, &map->textures.we));
		if (type == 4)
			return (parse_texture(line, &map->textures.ea));
		if (type == 5)
			return (parse_texture(line, &map->textures.d_closed));
		return (parse_texture(line, &map->textures.d_open));
	}
	else if (type == 7)
		return (parse_color(line, map->textures.f));
	else if (type == 8)
		return (parse_color(line, map->textures.c));
	return (1);
}

/*Analyzes passed line and get its type, then processes it depending which.*/
static int	handle_line(char *line, int fd, t_map *map)
{
	int	type;
	int	ret;

	type = get_line_type(line);
	if (type == -1)
	{
		free(line);
		free_gnl_buffer(fd);
		return (error_msg("Invalid line format in file"));
	}
	if (type >= 0)
	{
		ret = process_line(line, type, map);
		if (!ret)
		{
			free(line);
			free_gnl_buffer(fd);
			return (0);
		}
	}
	return (1);
}

/*General reading function line by line passing each to handle_line.*/
int	read_file_content(int fd, t_map *map)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		ret = handle_line(line, fd, map);
		if (!ret)
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
