/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_annex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:51:17 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/10 17:43:08 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that draw a vertical line of textured pixel on x abscissa
void	draw_vertical_line(t_games *games, int x, t_ray_params *ray, t_texture *tex)
{
	int		y;
	int		tex_y;
	//int		d;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		//tex_y = (int)tex_pos & (tex->height - 1);
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_pixel_color(tex, ray->tex_x, tex_y);
		put_pixel(&games->img, x, y, color);
		y++;
	}
}
// Funtion that just read the color of a pixel in texture
int	get_pixel_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

// Function that write a pixel on screen
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
