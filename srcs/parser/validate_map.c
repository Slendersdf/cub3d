/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:04:20 by caubert           #+#    #+#             */
/*   Updated: 2025/02/09 11:04:20 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*As the name goes, verifies the NSWE cell is within the map and single.*/
int	check_player_position(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("NSWE", map->grid[y][x]))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (error_msg("No player starting position found"));
	if (player_count > 1)
		return (error_msg("Multiple player starting positions found"));
	return (1);
}
