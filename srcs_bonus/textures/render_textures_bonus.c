/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:55:39 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/18 11:10:05 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* Background means floor and ceiling.
 * half_height is half the height of the window, which means where the horizon
 * is placed on the image.
 * Fills the screen pixel by pixel and line by line, if it's above half it will
 * be the ceiling's color and of not it will be the floor's color. */
void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	half_height;

	half_height = game->mlx->win_height / 2;
	y = 0;
	while (y < game->mlx->win_height)
	{
		x = 0;
		while (x < game->mlx->win_width)
		{
			if (y < half_height)
				put_pixel_to_img(game->screen, x, y, game->ceiling_color);
			else
				put_pixel_to_img(game->screen, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

/* Displays the image to the screen.
 * Calls the algorithm to show walls ingame and finalize the game's image.
 * It first places the background (floor and ceiling colors) then normally calls
 * the raycaster and finally mlx_put_image_to_window() which displays the final
 * rendered frame on screen. */
int	render_frame(t_game *game)
{
	int	x;

	if (!game || !game->mlx || !game->mlx->mlx || !game->mlx->win || \
			!game->screen)
		return (0);
	draw_background(game);
	x = 0;
	while (x < game->mlx->win_width)
	{
		cast_ray(game, x);
		x++;
	}
	draw_minimap(game);
	update_whip(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, \
			game->screen->img, 0, 0);
	return (1);
}
