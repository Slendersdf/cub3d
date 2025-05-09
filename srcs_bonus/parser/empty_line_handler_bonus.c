/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_line_handler_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:04:20 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:05 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || ft_strchr("NSEW", c));
}

static int	is_protected(t_map *map, int x, int y)
{
	if (y <= 0 || y >= map->height - 1)
		return (0);
	if (x <= 0 || (size_t)x >= ft_strlen(map->grid[y]) - 1)
		return (0);
	if ((size_t)x >= ft_strlen(map->grid[y - 1]) || map->grid[y - 1][x] == ' ')
		return (0);
	if ((size_t)x >= ft_strlen(map->grid[y + 1]) || map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ')
		return (0);
	if (map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	validate_current_map(t_map *map)
{
	int	x;
	int	y;

	if (!map->grid || map->height == 0)
		return (1);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_walkable(map->grid[y][x]) && !is_protected(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	handle_empty_line(t_map *map)
{
	if (map->grid && !map->height)
		return (error_msg("Empty map"));
	if (map->height > 0)
	{
		if (!validate_current_map(map))
			return (error_msg("Map not properly closed"));
		map->parsing_map = 1;
	}
	return (1);
}
