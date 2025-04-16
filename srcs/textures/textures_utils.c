/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:24:00 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/11 13:35:59 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Gets the pixel's color in an image. */
unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

/* Put a pixel in an image with given color. */
void	put_pixel_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* Creates a new MLX image. */
t_img	*create_new_image(t_mlx *mlx, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx->mlx, width, height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		free(img);
		return (NULL);
	}
	return (img);
}

/* Fills an image with specified color. */
void	fill_image(t_img *img, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			put_pixel_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

/* Draws a texture part on the screen. texture_num is the index of the texture,
 * 0=NO, 1=SO, 2=WE, 3=EA. x is a screen's column and params is the info on the
 * vertical line to draw. This is to be used with the raycaster. */
void	draw_texture_line(t_game *game, int texture_num, int x, \
		t_ray_params *params)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	double			step;
	double			tex_pos;

	if (texture_num < 0 || texture_num >= 6 || !game->textures[texture_num])
		return ;
	step = 1.0 * game->textures[texture_num]->height / params->line_height;
	tex_pos = (params->draw_start - game->mlx->win_height / 2 \
			+ params->line_height / 2) * step;
	y = params->draw_start;
	while (y < params->draw_end)
	{
		calculate_texture_y(game, tex_pos, texture_num, &tex_y);
		tex_pos += step;
		color = get_pixel_color(game->textures[texture_num], params->tex_x,
				tex_y);
		if (color != 0)
			put_pixel_to_img(game->screen, x, y, color);
		y++;
	}
}
