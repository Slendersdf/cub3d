/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:42:55 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/09 15:55:56 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_texture	load_one_texture(void *mlx, char *path)
{
	t_texture	tex;

	tex.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		tex.addr = NULL;
		return (tex);
	}
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length, &tex.endian);
	return (tex);
}

int	load_textures(t_games *games)
{
	games->textures[0] = load_one_texture(games->mlx->mlx, games->map->textures.no); // NO
	games->textures[1] = load_one_texture(games->mlx->mlx, games->map->textures.so); // SO
	games->textures[2] = load_one_texture(games->mlx->mlx, games->map->textures.we); // WE
	games->textures[3] = load_one_texture(games->mlx->mlx, games->map->textures.ea); // EA

	if (!games->textures[0].addr || !games->textures[1].addr ||
		!games->textures[2].addr || !games->textures[3].addr)
	{
		ft_printf("Error\nFailed to load one or more textures.\n");
		return (1);
	}
	return (0);
}

void	init_player(t_games *games)
{
	int		x, y;
	char	c;

	y = 0;
	while (y < games->map->height)
	{
		x = 0;
		while (games->map->grid[y][x])
		{
			c = games->map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				games->player.pos_x = x + 0.5;
				games->player.pos_y = y + 0.5;

				if (c == 'N')
				{
					games->player.dir_x = 0;
					games->player.dir_y = -1;
					games->player.plane_x = 0.66;
					games->player.plane_y = 0;
				}
				else if (c == 'S')
				{
					games->player.dir_x = 0;
					games->player.dir_y = 1;
					games->player.plane_x = -0.66;
					games->player.plane_y = 0;
				}
				else if (c == 'E')
				{
					games->player.dir_x = 1;
					games->player.dir_y = 0;
					games->player.plane_x = 0;
					games->player.plane_y = 0.66;
				}
				else if (c == 'W')
				{
					games->player.dir_x = -1;
					games->player.dir_y = 0;
					games->player.plane_x = 0;
					games->player.plane_y = -0.66;
				}
				return ;
			}
			x++;
		}
		y++;
	}
}
