/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:44:14 by caubert           #+#    #+#             */
/*   Updated: 2025/04/08 09:44:14 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_closed_door(t_game *game, int x, int y)
{
	int	i;

	if (game->map->grid[y][x] != 'D')
		return (0);
	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (!game->doors[i].is_open);
		i++;
	}
	return (1);
}

/* Checks if a movement is valid (no collision with a wall). */
int	is_valid_move(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map->height)
		return (0);
	if ((size_t)map_x >= ft_strlen(game->map->grid[map_y]))
		return (0);
	if (game->map->grid[map_y][map_x] == '1')
		return (0);
	if (is_closed_door(game, map_x, map_y))
		return (0);
	return (1);
}

/* Moves the player forward or backward. */
void	move_player_forward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Moves the player right or left by strafing with the use of plane_. */
void	move_player_sideways(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Rotates the player's view. */
void	rotate_player(t_game *game, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rotation_speed)
		- game->player.dir_y * sin(rotation_speed);
	game->player.dir_y = old_dir_x * sin(rotation_speed)
		+ game->player.dir_y * cos(rotation_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rotation_speed)
		- game->player.plane_y * sin(rotation_speed);
	game->player.plane_y = old_plane_x * sin(rotation_speed)
		+ game->player.plane_y * cos(rotation_speed);
}
