/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:00:43 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:06:56 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* Counts the total number of doors in the map. */
static int	count_doors(t_map *map)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/* Initializes the doors array, placed here for bonus conveniences. */
static int	allocate_doors(t_game *game, int door_count)
{
	game->doors = malloc(sizeof(t_door) * door_count);
	if (!game->doors)
		return (error_msg("Failed to allocate memory for doors"));
	game->door_count = door_count;
	return (1);
}

/* Fills the doors array with the position of each door and their initial state,
 * which is always set to close. */
static void	fill_doors_array(t_game *game)
{
	int	y;
	int	x;
	int	door_index;

	door_index = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			if (game->map->grid[y][x] == 'D')
			{
				game->doors[door_index].x = x;
				game->doors[door_index].y = y;
				game->doors[door_index].is_open = 0;
				door_index++;
			}
			x++;
		}
		y++;
	}
}

/* Whole initialization of doors and their parsing on the map. */
int	init_doors(t_game *game)
{
	int	door_count;

	if (!game || !game->map || !game->map->grid)
		return (error_msg("Game structure not properly initialized"));
	door_count = count_doors(game->map);
	if (door_count == 0)
		return (1);
	if (!allocate_doors(game, door_count))
		return (0);
	fill_doors_array(game);
	return (1);
}
