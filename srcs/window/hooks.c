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

/* Handles keypress events by calling appropriate functions in /player. */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		mlx_loop_end(game->mlx->mlx);
		return (1);
	}
	else if (keycode == XK_w)
		game->keys.w = 1;
	else if (keycode == XK_s)
		game->keys.s = 1;
	else if (keycode == XK_a)
		game->keys.a = 1;
	else if (keycode == XK_d)
		game->keys.d = 1;
	else if (keycode == XK_Left)
		game->keys.left = 1;
	else if (keycode == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 0;
	else if (keycode == XK_s)
		game->keys.s = 0;
	if (keycode == XK_a)
		game->keys.a = 0;
	if (keycode == XK_d)
		game->keys.d = 0;
	if (keycode == XK_Left)
		game->keys.left = 0;
	if (keycode == XK_Right)
		game->keys.right = 0;
	return (0);
}

/* Handles close up of the window. */
int	handle_close(t_game *game)
{
	mlx_loop_end(game->mlx->mlx);
	return (0);
}

/* Setup hooks for events. */
int	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, \
				game);
	mlx_hook(game->mlx->win, DestroyNotify, StructureNotifyMask, \
				&handle_close, game);
	return (1);
}
