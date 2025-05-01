/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:56 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:06:11 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	free_whip(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->whip.frame_count)
	{
		if (game->whip.frames[i])
		{
			if (game->whip.frames[i]->img)
				mlx_destroy_image(game->mlx->mlx, \
						game->whip.frames[i]->img);
			free(game->whip.frames[i]);
		}
		i++;
	}
	free(game->whip.frames);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->whip.frames)
		free_whip(game);
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
	if (game->doors)
		free(game->doors);
	if (game->map)
		free_map(game->map);
	free(game);
}
