/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:59:56 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 17:59:56 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*Frees the whole game features like the window and display along with the
 * textures by calling free_render(). */
void	free_game(t_game *game)
{
	if (!game)
		return ;
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
