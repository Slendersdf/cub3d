/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:27:02 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:12 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	validate_map_format(t_map *map)
{
	int	i;

	if (!map || !map->grid || map->height == 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!is_valid_map_line(map->grid[i]))
			return (error_msg("Empty or space-only line in map"));
		if (!check_trailing_chars(map->grid[i]))
			return (error_msg("Spaces are not allowed within the map"));
		i++;
	}
	return (1);
}

int	verify_map_started(t_map *map)
{
	if (!map->grid || map->height == 0)
		return (error_msg("Empty map"));
	return (1);
}

int	verify_map_content(t_map *map)
{
	int	i;

	if (!map->grid || map->height == 0)
		return (error_msg("Empty map"));
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i] || !*map->grid[i])
		{
			free_grid(map->grid, map->height);
			map->grid = NULL;
			return (error_msg("Empty line in map after cleanup"));
		}
		i++;
	}
	return (1);
}
