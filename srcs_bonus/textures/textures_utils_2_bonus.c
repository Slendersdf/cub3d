/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:33:37 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:10:09 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	calculate_texture_y(t_game *game, double tex_pos, int texture_num, \
					int *tex_y)
{
	*tex_y = (int)tex_pos;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= game->textures[texture_num]->height)
		*tex_y = game->textures[texture_num]->height - 1;
}
