/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:29:09 by caubert           #+#    #+#             */
/*   Updated: 2025/02/10 18:29:09 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Frees an array of strings and the array itself. */
void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* Frees all texture paths stored in the textures structure t_textures. */
static void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
}

/* Frees the entire map structure t_map including texture paths and the grid. */
void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	free_textures(&map->textures);
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

/* Frees a grid of strings with a specified height. */
void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
		free(grid[i++]);
	free(grid);
}

/* Empties the gnl buffer by consuming and freeing all remaining lines. */
void	free_gnl_buffer(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}
