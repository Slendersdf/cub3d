/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:38:19 by caubert           #+#    #+#             */
/*   Updated: 2025/02/08 18:38:19 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	finalize_map_parsing(t_map *map)
{
	if (!verify_map_content(map))
		return (0);
	if (!validate_map_format(map))
		return (0);
	if (!validate_map_spaces(map))
		return (0);
	if (!check_player_position(map))
		return (0);
	return (1);
}

static int	handle_empty_line(t_map *map)
{
	if (map->grid)
	{
		if (!verify_map_started(map))
			return (0);
		return (error_msg("Empty line or space in map not allowed"));
	}
	return (1);
}

/*Duplicates the map.*/
static int	create_new_grid(t_map *map, char *new_line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!new_grid)
	{
		free_grid(map->grid, map->height);
		map->grid = NULL;
		return (error_msg_free("Memory allocation failed", new_line));
	}
	i = -1;
	while (++i < map->height)
		new_grid[i] = map->grid[i];
	new_grid[i] = new_line;
	free(map->grid);
	map->grid = new_grid;
	return (1);
}

static int	update_map_properties(t_map *map, char *new_line)
{
	if (!create_new_grid(map, new_line))
		return (0);
	map->height++;
	map->width = ft_max(map->width, ft_strlen(new_line));
	return (1);
}

/*Starts treatment of supposed map lines.*/
int	parse_map_line(char *line, t_map *map)
{
	char	*new_line;

	if (!is_map_line(line))
		return (handle_empty_line(map));
	new_line = dup_line_with_spaces(line);
	if (!new_line)
	{
		free_grid(map->grid, map->height);
		map->grid = NULL;
		return (error_msg("Invalid character in map line"));
	}
	if (!update_map_properties(map, new_line))
		return (0);
	return (1);
}
