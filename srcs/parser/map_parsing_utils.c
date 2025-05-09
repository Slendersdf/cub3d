/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:27:02 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 12:27:02 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Validates the map format, checking for empty lines or invalid spaces. */
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

/* Verifies that the map has been started (that it's not empty). */
int	verify_map_started(t_map *map)
{
	if (!map->grid || map->height == 0)
		return (error_msg("Empty map"));
	return (1);
}

/* Validates that the map content is not empty after processing. */
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
