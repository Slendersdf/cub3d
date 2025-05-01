/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:53:49 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:08:32 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* Initializes game's structure values. floor and ceiling colors are set to 0
 * (black) before being edited further.
 * Player's speed is set to 0.05 since in a raycaster, positions are relatives
 * to the map's grid. 1 is a tile, so a speed of 0.05 means the player will
 * likely walk 5% of a tile per frame, needing 20 frames to walk past this tile
 * (1 / 0.05 = 20).
 * Same goes for the rotation's speed. We later use trigonometry in which
 * rotation is in rads. 0.03 is roughly 1.7°. If we play in 60 fps, it means we
 * can fully rotate (360°) in about 3.5 seconds, which is supposedly comfortable
 * for most player. */
t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = NULL;
	game->mlx = NULL;
	game->textures = NULL;
	game->screen = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->player.move_speed = 0.05;
	game->player.rotation_speed = 0.03;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.e = 0;
	game->mouse_captured = 0;
	game->doors = NULL;
	game->door_count = 0;
	return (game);
}
