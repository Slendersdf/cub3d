/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:44:18 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/08 16:44:29 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(
		game->img.img,
		&game->img.bpp,
		&game->img.line_length,
		&game->img.endian
	);
	return (0);
}
