/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:42:40 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/16 12:50:18 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char *whip_frame_paths[WHIP_FRAME_COUNT] = {
	"./textures/whip/1.xpm",
	"./textures/whip/2.xpm",
	"./textures/whip/3.xpm",
	"./textures/whip/4.xpm",
	"./textures/whip/5.xpm",
	"./textures/whip/6.xpm",
	"./textures/whip/7.xpm",
	"./textures/whip/8.xpm",
	"./textures/whip/9.xpm",
	"./textures/whip/10.xpm",
	"./textures/whip/11.xpm",
	"./textures/whip/12.xpm",
	"./textures/whip/13.xpm",
	"./textures/whip/14.xpm",
	"./textures/whip/15.xpm",
	"./textures/whip/16.xpm",
	"./textures/whip/17.xpm",
	"./textures/whip/18.xpm"
};

void	init_whip(t_game *game)
{
	int i;

	game->whip.frame_count = WHIP_FRAME_COUNT; // le nombre d'image a changer
	game->whip.frames = malloc(sizeof(t_img *) * WHIP_FRAME_COUNT);
	i = 0;
	while (i < WHIP_FRAME_COUNT)
	{
		game->whip.frames[i] = load_texture_file(game, whip_frame_paths[i]);
		if (!game->whip.frames[i])
		{
			printf("Failed to load whip frame: %s\n", whip_frame_paths[i]);
			exit(1); // ou bien return une erreur propre
		}
		i++;
	}
	game->whip.current_frame = 0;
	game->whip.is_active = 0;
}

void	update_whip(t_game *game)
{
	if (game->whip.is_active)
	{
		draw_whip_frame(game, game->whip.frames[game->whip.current_frame]);
		game->whip.current_frame++;
		if (game->whip.current_frame >= game->whip.frame_count)
			game->whip.is_active = 0;
	}
}

void	draw_whip_frame(t_game *game, t_img *frame)
{
	int pos_x;
	int pos_y;

	if (!frame || !frame->img)
		return ;

	pos_x = (game->mlx->win_width - frame->width) / 2;
	pos_y = game->mlx->win_height - frame->height;

	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, frame->img, pos_x, pos_y);
}
