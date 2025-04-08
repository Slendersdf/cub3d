/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:19:49 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/08 16:39:19 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_frame(t_game *game)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Rayon pour cette colonne
		double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		int map_x = (int)game->player.pos_x;
		int map_y = (int)game->player.pos_y;

		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double side_dist_x, side_dist_y;

		int step_x, step_y, hit = 0, side;

		// Détermination des pas et distances initiales
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
		}

		// DDA
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map->grid[map_y][map_x] == '1')
				hit = 1;
		}

		// Distance perpendiculaire au mur
		double perp_wall_dist = (side == 0)
			? (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x
			: (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

		// Paramètres du rendu
		t_ray_params ray;
		ray.line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_start < 0) ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + SCREEN_HEIGHT / 2;
		if (ray.draw_end >= SCREEN_HEIGHT) ray.draw_end = SCREEN_HEIGHT - 1;

		// Coordonnée exacte de l’impact du rayon sur le mur
		if (side == 0)
			ray.wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
		else
			ray.wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
		ray.wall_x -= floor(ray.wall_x);

		ray.tex_x = (int)(ray.wall_x * (double)TEXTURE_WIDTH);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			ray.tex_x = TEXTURE_WIDTH - ray.tex_x - 1;

		// Sélection de la texture
		t_texture *tex;
		if (side == 0)
			tex = (ray_dir_x < 0) ? &game->textures[2] : &game->textures[3]; // WE / EA
		else
			tex = (ray_dir_y < 0) ? &game->textures[0] : &game->textures[1]; // NO / SO

		draw_vertical_line(game, x, &ray, tex);
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray_params *ray, t_texture *tex)
{
	int		y;
	int		tex_y;
	int		d;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_pixel_color(tex, ray->tex_x, tex_y);
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

int	get_pixel_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


