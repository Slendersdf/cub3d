/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:39:39 by caubert           #+#    #+#             */
/*   Updated: 2025/04/15 19:39:39 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	find_door_index(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

static void	toggle_door_state(t_game *game, int door_x, int door_y, int index)
{
	if (game->map->grid[door_y][door_x] == 'D' && index != -1)
	{
		game->map->grid[door_y][door_x] = '0';
		game->doors[index].is_open = 1;
	}
	else if (game->map->grid[door_y][door_x] == '0' && index != -1)
	{
		game->map->grid[door_y][door_x] = 'D';
		game->doors[index].is_open = 0;
	}
}

void	handle_door_interaction(t_game *game)
{
	int	door_x;
	int	door_y;
	int	index;

	if (!game->keys.e)
		return ;
	game->keys.e = 0;
	door_x = (int)(game->player.pos_x + game->player.dir_x);
	door_y = (int)(game->player.pos_y + game->player.dir_y);
	if (door_x >= 0 && door_y >= 0 && door_y < game->map->height && \
			(size_t)door_x < ft_strlen(game->map->grid[door_y]))
	{
		index = find_door_index(game, door_x, door_y);
		toggle_door_state(game, door_x, door_y, index);
	}
}
