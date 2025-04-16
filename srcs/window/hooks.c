/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:55:59 by caubert           #+#    #+#             */
/*   Updated: 2025/04/14 15:48:12 by fpaulas-         ###   ########.fr       */
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
	else if (keycode == XK_e)
		game->keys.e = 1;
	else if (keycode == XK_m)
		toggle_mouse_capture(game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 0;
	else if (keycode == XK_s)
		game->keys.s = 0;
	else if (keycode == XK_a)
		game->keys.a = 0;
	else if (keycode == XK_d)
		game->keys.d = 0;
	else if (keycode == XK_Left)
		game->keys.left = 0;
	else if (keycode == XK_Right)
		game->keys.right = 0;
	else if (keycode == XK_e)
		game->keys.e = 0;
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	prev_x;
	int			diff_x;
	double		rotation_speed;

	(void)y;
	prev_x = -1;
	if (!game->mouse_captured)
		return (0);
	if (prev_x == -1)
	{
		prev_x = x;
		return (0);
	}
	diff_x = x - prev_x;
	if (diff_x == 0)
		return (0);
	rotation_speed = game->player.rotation_speed * diff_x * 0.05;
	rotate_player(game, rotation_speed);
	adjust_mouse_position(x, &prev_x, game);
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
	mlx_hook(game->mlx->win, MotionNotify, PointerMotionMask, \
				&handle_mouse_move, game);
	mlx_hook(game->mlx->win, 4, 1L << 2, mouse_press, game);
	return (1);
}
