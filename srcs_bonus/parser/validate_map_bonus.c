/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:04:20 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:52 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/*
static int	is_walkable(char c)
{
	return (c == '0' || ft_strchr("NSWE", c));
}

static int	check_adjacent_spaces(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1)
		return (0);
	if (x == 0 || (size_t)x == ft_strlen(map->grid[y]) - 1)
		return (0);
	if (map->grid[y - 1][x] == ' ')
		return (0);
	if (map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ')
		return (0);
	if (map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

//Verifies with above functions that '0' cells aren't touching void spaces.//
int	validate_map_spaces(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_walkable(map->grid[y][x]))
			{
				if (!check_adjacent_spaces(map, x, y))
					return (error_msg("Map not properly closed everywhere"));
			}
			x++;
		}
		y++;
	}
	return (1);
}
*/
/*As the name goes, verifies the NSWE cell is within the map and single.*/
int	check_player_position(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("NSWE", map->grid[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (error_msg("No player starting position found"));
	if (player_count > 1)
		return (error_msg("Multiple player starting positions found"));
	return (1);
}
