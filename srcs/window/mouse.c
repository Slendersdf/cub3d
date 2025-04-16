/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:07:16 by caubert           #+#    #+#             */
/*   Updated: 2025/04/14 15:48:38 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && !game->whip.is_active)
	{
		game->whip.is_active = 1;
		game->whip.current_frame = 0;
		game->whip.current_delay = 0;
	}
	return (0);
}

void	toggle_mouse_capture(t_game *game)
{
	game->mouse_captured = !game->mouse_captured;
	if (game->mouse_captured)
	{
		mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
		mlx_mouse_move(game->mlx->mlx, game->mlx->win, \
				game->mlx->win_width / 2, game->mlx->win_height / 2);
	}
	else
		mlx_mouse_show(game->mlx->mlx, game->mlx->win);
}
