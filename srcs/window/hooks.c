/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:55:59 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 17:55:59 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		mlx_loop_end(game->mlx->mlx);
		return (1);
	}
	return (0);
}

int	handle_close(t_game *game)
{
	mlx_loop_end(game->mlx->mlx);
	return (0);
}

int	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->mlx->win, DestroyNotify, StructureNotifyMask, \
				&handle_close, game);
	return (1);
}
