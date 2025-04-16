/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:42:40 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/16 14:36:14 by fpaulas-         ###   ########.fr       */
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
	game->whip.frame_count = WHIP_FRAME_COUNT; // le nombre d'image a changer
	game->whip.frames = malloc(sizeof(t_img *) * WHIP_FRAME_COUNT);
	if (!game->whip.frames)
	{
			printf("Failed to allocate whip frame.\n");
			exit(1);
	}
	game->whip.frame_delay = malloc(sizeof(int) * WHIP_FRAME_COUNT);
	if (!game->whip.frame_delay)
	{
			printf("Failed to allocate whip frame delays.\n");
			exit(1);
	}
	i = 0;
	while (i < WHIP_FRAME_COUNT)
	{
		game->whip.frames[i] = load_texture_file(game, whip_frame_paths[i]);
		if (!game->whip.frames[i])
		{
			printf("Failed to load whip frame: %s\n", whip_frame_paths[i]);
			exit(1); // ou bien return une erreur propre
		}
		// et ici on définit le délai en fonction de l'image
		if (i < 4)
		game->whip.frame_delay[i] = 3;  // plus rapide au début
		else if (i < 8)
			game->whip.frame_delay[i] = 5;  // ralentit un peu
		else
			game->whip.frame_delay[i] = 7;  // impact plus long en fin
		i++;
	}
	game->whip.current_frame = 0;
	game->whip.is_active = 0;
}

void update_whip(t_game *game)
{
	if (game->whip.is_active)
	{
		// afficher la frame actuelle
		draw_whip_frame(game, game->whip.frames[game->whip.current_frame]);

		// attendre le bon nombre de frames avant de passer à la suivante
		if (game->whip.current_delay < game->whip.frame_delay[game->whip.current_frame])
		{
			game->whip.current_delay++;
			return;
		}
		game->whip.current_delay = 0;
		game->whip.current_frame++;

		// fin de l'animation
		if (game->whip.current_frame >= game->whip.frame_count)
		{
			game->whip.is_active = 0;
			game->whip.current_frame = 0;
			printf("current_frame: %d / %d\n", game->whip.current_frame, game->whip.frame_count);
		}
	}
}

void	draw_whip_frame(t_game *game, t_img *frame)
{
	int pos_x;
	int pos_y;

	if (!frame || !frame->img)
		return ;

	pos_x = (game->mlx->win_width - frame->width) / 1.1;
	pos_y = game->mlx->win_height - frame->height;

	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, frame->img, pos_x, pos_y);
}
