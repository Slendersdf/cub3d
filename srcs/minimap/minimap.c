/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:03 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/14 16:19:27 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function to draw square(s)
// Useful to draw the minimap and other quadrilaterals
void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int i, j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_img(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// Function to draw the player on the minimap
void	draw_player_on_minimap(t_game *game, int offset_x, int offset_y)
{
	int player_x, player_y;

	player_x = offset_x + game->player.pos_x * MINIMAP_SCALE;
	player_y = offset_y + game->player.pos_y * MINIMAP_SCALE;

	draw_square(game->screen, player_x - 2, player_y - 2, 4, 0xFF0000); // rouge
}

// Function to draw the minimap and the player, square by square
void	draw_minimap(t_game *game)
{
	int i, j;
	int color;
	int offset_x, offset_y;

	offset_x = 10; // Décalage depuis le bord gauche
	offset_y = game->mlx->win_height - game->map->height * MINIMAP_SCALE - 10;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (j < (int)ft_strlen(game->map->grid[i]) && game->map->grid[i][j] == '1')
				color = 0x555555;  // murs : gris
			else
				color = 0xAAAAAA;  // sol : clair

			draw_square(game->screen, offset_x + j * MINIMAP_SCALE,
				offset_y + i * MINIMAP_SCALE, MINIMAP_SCALE, color);
			j++;
		}
		i++;
	}
	draw_player_on_minimap(game, offset_x, offset_y);
}
