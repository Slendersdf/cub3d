/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:51:25 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:08:49 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->textures.no = NULL;
	map->textures.so = NULL;
	map->textures.we = NULL;
	map->textures.ea = NULL;
	map->textures.d_open = NULL;
	map->textures.d_closed = NULL;
	map->textures.f[0] = -1;
	map->textures.f[1] = -1;
	map->textures.f[2] = -1;
	map->textures.c[0] = -1;
	map->textures.c[1] = -1;
	map->textures.c[2] = -1;
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->parsing_map = 0;
	return (map);
}
