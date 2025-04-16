/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:42:40 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/16 16:24:31 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char *whip_frame_paths[WHIP_FRAME_COUNT] = {
	"./textures/whip/1_bigger.xpm",
	"./textures/whip/7_bigger.xpm",
	"./textures/whip/9_bigger.xpm",
	"./textures/whip/12_bigger.xpm",
	"./textures/whip/14_bigger.xpm",
	"./textures/whip/16_bigger.xpm",
};

void	init_whip(t_game *game)
{
	int i;

	game->whip.current_delay = 0;
	game->whip.frame_count = WHIP_FRAME_COUNT;
	game->whip.frames = malloc(sizeof(t_img *) * WHIP_FRAME_COUNT);
	if (!game->whip.frames)
		exit(1);

	i = 0;
	while (i < WHIP_FRAME_COUNT)
	{
		game->whip.frames[i] = load_texture_file(game, whip_frame_paths[i]);
		if (!game->whip.frames[i])
		{
			printf("Failed to load whip frame: %s\n", whip_frame_paths[i]);
			exit(1);
		}
		i++;
	}
	game->whip.frame_delay = 20; // délai unique pour tout le fouet
	game->whip.current_frame = 0;
	game->whip.is_active = 0;
}

void	update_whip(t_game *game)
{
	// Si inactif : on affiche la frame 0 en continu
	if (!game->whip.is_active)
	{
		draw_whip_frame(game, game->whip.frames[0]);
		return;
	}

	// Affiche la frame actuelle pendant l'animation
	draw_whip_frame(game, game->whip.frames[game->whip.current_frame]);

	// Attendre le délai défini avant de passer à la suivante
	if (game->whip.current_delay < game->whip.frame_delay)
	{
		game->whip.current_delay++;
		return;
	}

	game->whip.current_delay = 0;
	game->whip.current_frame++;

	// Fin de l'animation
	if (game->whip.current_frame >= game->whip.frame_count)
	{
		game->whip.is_active = 0;
		game->whip.current_frame = 0;
	}
}

void	draw_whip_frame(t_game *game, t_img *frame)
{
	int	x, y;
	int	dst_x, dst_y;
	int	color;

	if (!frame || !frame->img)
		return ;

	dst_x = (game->mlx->win_width - frame->width) / 1.000111;
	dst_y = game->mlx->win_height - frame->height + 10;

	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			color = get_pixel_color(frame, x, y);
			// si color != transparent (par exemple 0xFF000000 pour transparence)
			if ((color & 0xFF000000) != 0xFF000000)
				put_pixel_to_img(game->screen, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}
