/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:44:18 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/09 15:56:13 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_image(t_games *games)
{
	games->img.img = mlx_new_image(games->mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!games->img.img)
		return (1);
	games->img.addr = mlx_get_data_addr(
		games->img.img,
		&games->img.bpp,
		&games->img.line_length,
		&games->img.endian
	);
	return (0);
}
