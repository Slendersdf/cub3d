/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:46:08 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 17:46:08 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_window(t_game *game)
{
	if (!game || !game->map)
		return (error_msg("Game structure not initialized"));
	game->mlx = init_mlx_struct();
	if (!game->mlx)
		return (error_msg("MLX structure allocation failed"));
	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
	{
		free(game->mlx);
		return (error_msg("MLX initialization failed"));
	}
	game->mlx->win = mlx_new_window(game->mlx->mlx, game->mlx->win_width, \
			game->mlx->win_height, "cub3D");
	if (!game->mlx->win)
	{
		mlx_destroy_display(game->mlx->mlx);
		free(game->mlx->mlx);
		free(game->mlx);
		return (error_msg("Window creation failed"));
	}
	return (1);
}
