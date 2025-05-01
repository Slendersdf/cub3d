/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:02:27 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:12:22 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d.h"

int	setup_graphics(t_game *game)
{
	if (!init_window(game))
		return (0);
	init_player(game);
	if (!init_doors(game))
		return (0);
	setup_hooks(game);
	init_whip(game);
	if (!init_render(game))
		return (0);
	return (1);
}
