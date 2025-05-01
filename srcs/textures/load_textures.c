/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:08:27 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/08 11:08:27 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Converts RGB into an int usable by the MLX.
 * We shift r and g values by 8 bits (16-23 and 8-15) and let b be at pos 0-7,
 * and combine it all into one usable number using "|". */
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* Charges a XPM from a file.
 * We create a t_img to store image's informations.
 * mlx_xpm_file_to_image() loads the XPM file and returns a pointer to the image
 * while filling its dimensions height and width.
 * mlx_get_data_addr() get the data address of the image and fills extra infos
 * such as bits per pixel, line length, so on.
 * In the end, it returns the loaded and allocated image. */
static t_img	*load_texture_file(t_game *game, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx->mlx, path, \
			&img->width, &img->height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx->mlx, img->img);
		free(img);
		return (NULL);
	}
	return (img);
}

/* Calls the load of texture files for each index of the textures array. */
static int	load_texture_images(t_game *game)
{
	int	i;

	game->textures[0] = load_texture_file(game, game->map->textures.no);
	game->textures[1] = load_texture_file(game, game->map->textures.so);
	game->textures[2] = load_texture_file(game, game->map->textures.we);
	game->textures[3] = load_texture_file(game, game->map->textures.ea);
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i])
		{
			free_all_textures(game);
			return (error_msg("Failed to load texture"));
		}
		i++;
	}
	return (1);
}

/* Charges all textures.
 * Meaning it loads the walls textures by filling an array for the 4 walls types
 * and calls the above load_texture_file() for each of them.
 * It then creates the correctly encoded int required to show the floor and
 * ceiling colors. */
int	load_textures(t_game *game)
{
	int	i;

	game->textures = malloc(sizeof(t_img *) * 4);
	if (!game->textures)
		return (error_msg("Failed to allocate memory for textures"));
	i = 0;
	while (i < 4)
		game->textures[i++] = NULL;
	if (!load_texture_images(game))
		return (0);
	game->floor_color = create_rgb(game->map->textures.f[0], \
			game->map->textures.f[1], game->map->textures.f[2]);
	game->ceiling_color = create_rgb(game->map->textures.c[0], \
			game->map->textures.c[1], game->map->textures.c[2]);
	return (1);
}
