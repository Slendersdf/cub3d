/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:45:00 by caubert           #+#    #+#             */
/*   Updated: 2025/04/08 10:45:00 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initializes image for the render.
 * Basically means we create a back-buffer here in which we can draw what we
 * want before showing it to the screen, storing it in the screen variable, by
 * calling create_new_image() which is placed in textures_utils.c. */
static int	init_render_image(t_game *game)
{
	game->screen = create_new_image(game->mlx, game->mlx->win_width, \
			game->mlx->win_height);
	if (!game->screen)
		return (error_msg("Failed to create rendering image"));
	return (1);
}

/* Initializes texture's render.
 * It ensures all prerequisites such as game and mlx are valids before doing
 * anything. It then calls load_textures() to, well, load textures of the walls
 * from their XPM files.
 * It then calls the above function, init_render_image() to create the
 * "workspace". And then it calls render_frame to the first ingame image, before
 * the player moves.
 * It always frees resources in case of an error. */
int	init_render(t_game *game)
{
	if (!game || !game->mlx || !game->mlx->mlx || !game->mlx->win)
		return (error_msg("Game not properly initialized for rendering"));
	if (!load_textures(game))
		return (0);
	if (!init_render_image(game))
	{
		free_all_textures(game);
		return (0);
	}
	if (!render_frame(game))
	{
		free_all_textures(game);
		free_texture(game->mlx, game->screen);
		game->screen = NULL;
		return (error_msg("Failed to render frame"));
	}
	return (1);
}
