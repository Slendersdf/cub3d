/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:20:28 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:18:22 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	adjust_mouse_position(int x, int *prev_x, t_game *game)
{
	if (x < 100 || x > game->mlx->win_width - 100)
	{
		mlx_mouse_move(game->mlx->mlx, game->mlx->win, \
				game->mlx->win_width / 2, game->mlx->win_height / 2);
		*prev_x = game->mlx->win_width / 2;
	}
	else
		*prev_x = x;
}
