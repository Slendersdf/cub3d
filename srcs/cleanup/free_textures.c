/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:20:37 by caubert           #+#    #+#             */
/*   Updated: 2025/04/08 11:20:37 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Frees the specified indexed texture by call of mlx_destroy_image. */
void	free_texture(t_mlx *mlx, t_img *texture)
{
	if (!texture)
		return ;
	if (texture->img && mlx && mlx->mlx)
		mlx_destroy_image(mlx->mlx, texture->img);
	free(texture);
}

/* Frees the whole array of pointers "textures" by using free_texture function.
 * */
void	free_all_textures(t_game *game)
{
	int	i;

	if (!game || !game->textures)
		return ;
	i = 0;
	while (i < 6)
	{
		free_texture(game->mlx, game->textures[i]);
		i++;
	}
	free(game->textures);
	game->textures = NULL;
}
