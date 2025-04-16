/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:56 by caubert           #+#    #+#             */
/*   Updated: 2025/04/16 16:27:57 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	if (game->whip.frames)
	{
		while (i < game->whip.frame_count)
		{
			if (game->whip.frames[i])
			{
				if (game->whip.frames[i]->img)
					mlx_destroy_image(game->mlx->mlx, game->whip.frames[i]->img);
				free(game->whip.frames[i]);
			}
			i++;
		}
		free(game->whip.frames);
	}
	free_render(game);
	if (game->mlx)
	{
		if (game->mlx->win)
			mlx_destroy_window(game->mlx->mlx, game->mlx->win);
		if (game->mlx->mlx)
		{
			mlx_destroy_display(game->mlx->mlx);
			free(game->mlx->mlx);
		}
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	free(game);
}
