/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:02:36 by caubert           #+#    #+#             */
/*   Updated: 2025/04/08 10:02:36 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initializes the pos and direction of the player depending on the map starting
 * point.
 * We add 0.5 to the position which means 50% of the current tile for both x and
 * y axis so we're exactly at the center of the starting tile. */
void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (game->map->grid[y][x])
		{
			if (ft_strchr("NSEW", game->map->grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				init_player_direction(game, game->map->grid[y][x]);
				game->map->grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

/* Initializes the player's direction and camera position depending on the
 * orientation.
 * dir = direction in which the player look.
 * plane = FOV = (2 * atan(0.66)).
 * 0.66 is arbitrary but the closer we are to 1, the larger and distorded the
 * FOV will appear, and the closer we are to 0, the tunneler view we'll have.
 * The plane vector is always perpendicular to the player's view, and thus sets
 * the FOV angle, in degrees. */
void	init_player_direction(t_game *game, char orientation)
{
	if (orientation == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (orientation == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (orientation == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}
