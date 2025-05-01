/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:03 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/18 11:06:47 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	draw_square_at(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel_to_img(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_dot(t_img *img, int x, int y)
{
	int	i;
	int	j;

	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			put_pixel_to_img(img, x + j, y + i, 0xFF0000);
			j++;
		}
		i++;
	}
}

// Function to draw the player on the minimap
void	draw_player_on_minimap(t_game *game, int offset_x, int offset_y)
{
	int	player_x;
	int	player_y;

	player_x = offset_x + game->player.pos_x * MINIMAP_SCALE;
	player_y = offset_y + game->player.pos_y * MINIMAP_SCALE;
	draw_player_dot(game->screen, player_x, player_y);
}

static void	draw_map_tile(t_game *game, int i, int j, int *offsets)
{
	int	tile_x;
	int	tile_y;
	int	color;

	tile_x = offsets[0] + j * MINIMAP_SCALE;
	tile_y = offsets[1] + i * MINIMAP_SCALE;
	if (j < (int)ft_strlen(game->map->grid[i]) && game->map->grid[i][j] == '1')
		color = 0x555555;
	else
		color = 0xAAAAAA;
	draw_square_at(game->screen, tile_x, tile_y, color);
}

// Function to draw the minimap and the player, square by square
void	draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	offsets[2];

	offsets[0] = 10;
	offsets[1] = game->mlx->win_height - game->map->height * MINIMAP_SCALE - 10;
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			draw_map_tile(game, i, j, offsets);
			j++;
		}
		i++;
	}
	draw_player_on_minimap(game, offsets[0], offsets[1]);
}
