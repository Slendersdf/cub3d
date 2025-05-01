/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:52:43 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:06:22 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* Frees rendered resources.
 * Since screen is a variable representing the screen (duh) is has to be freed
 * separately once everything else has been freed.*/
void	free_render(t_game *game)
{
	if (!game)
		return ;
	free_all_textures(game);
	if (game->screen)
	{
		free_texture(game->mlx, game->screen);
		game->screen = NULL;
	}
}
