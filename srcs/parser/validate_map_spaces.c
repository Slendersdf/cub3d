/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:30:42 by caubert           #+#    #+#             */
/*   Updated: 2025/04/15 13:30:42 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Determines if a character rerpesents a walkable position. */
static int	is_walkable(char c)
{
	return (c == '0' || ft_strchr("NSEW", c));
}

/* Checks if a character represents an empty space or void. */
static int	is_valid_space(char c)
{
	return (c == ' ' || c == '\0');
}

/* Verifies that walkable positions aren't adjacent to void spaces. */
static int	check_adjacent_to_void(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1)
		return (0);
	if (x == 0 || (size_t)x >= ft_strlen(map->grid[y]) - 1)
		return (0);
	if (y > 0 && ((size_t)x >= ft_strlen(map->grid[y - 1]) || \
				is_valid_space(map->grid[y - 1][x])))
		return (0);
	if (y < map->height - 1 && ((size_t)x >= ft_strlen(map->grid[y + 1]) || \
				is_valid_space(map->grid[y + 1][x])))
		return (0);
	if (x > 0 && is_valid_space(map->grid[y][x - 1]))
		return (0);
	if ((size_t)x < ft_strlen(map->grid[y]) - 1 && \
				is_valid_space(map->grid[y][x + 1]))
		return (0);
	return (1);
}

/* Replaces all space characters with walls for consistency. */
static void	replace_spaces_with_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			x++;
		}
		y++;
	}
}

/* Validates that the map is properly enclosed, with no paths to void spaces. */
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
				if (!check_adjacent_to_void(map, x, y))
					return (error_msg("Map not properly closed"));
			}
			x++;
		}
		y++;
	}
	replace_spaces_with_walls(map);
	return (1);
}
