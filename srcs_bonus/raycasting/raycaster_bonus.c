/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:19:49 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/18 11:08:20 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* Function to define in which direction we will jump in the grid
 * It also calculate the distance between player and first line or column */
void	init_step_and_side(t_ray_vars *v, t_game *g)
{
	if (v->ray_dir_x < 0)
	{
		v->step_x = -1;
		v->side_dist_x = (g->player.pos_x - v->map_x) * v->delta_dist_x;
	}
	else
	{
		v->step_x = 1;
		v->side_dist_x = (v->map_x + 1.0 - g->player.pos_x) * v->delta_dist_x;
	}
	if (v->ray_dir_y < 0)
	{
		v->step_y = -1;
		v->side_dist_y = (g->player.pos_y - v->map_y) * v->delta_dist_y;
	}
	else
	{
		v->step_y = 1;
		v->side_dist_y = (v->map_y + 1.0 - g->player.pos_y) * v->delta_dist_y;
	}
}

/* Function that uses DDA (Digitial Differential Analyzer) algorthim
 * To run through the map until a wall is found (hit) */
void	perform_dda(t_ray_vars *v, t_game *g)
{
	while (!v->hit)
	{
		if (v->side_dist_x < v->side_dist_y)
		{
			v->side_dist_x += v->delta_dist_x;
			v->map_x += v->step_x;
			v->side = 0;
		}
		else
		{
			v->side_dist_y += v->delta_dist_y;
			v->map_y += v->step_y;
			v->side = 1;
		}
		if (g->map->grid[v->map_y][v->map_x] == '1')
			v->hit = 1;
		else if (g->map->grid[v->map_y][v->map_x] == 'D')
			handle_door_hit(v, g);
	}
}

/* Function that calculates the exact distance between player and a wall
 * after the player hits a wall */
void	compute_wall_distance(t_ray_vars *v, t_game *g)
{
	if (v->side == 0)
		v->perp_wall_dist = (v->map_x - g->player.pos_x + \
				(1 - v->step_x) / 2.0) / v->ray_dir_x;
	else
		v->perp_wall_dist = (v->map_y - g->player.pos_y + \
				(1 - v->step_y) / 2.0) / v->ray_dir_y;
}

/* Function that calculates height and vertical position of the wall
 * displayed */
void	calculate_ray_params(t_ray_params *r, t_ray_vars *v, t_game *g)
{
	r->line_height = (int)(g->mlx->win_height / v->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + g->mlx->win_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + g->mlx->win_height / 2;
	if (r->draw_end >= g->mlx->win_height)
		r->draw_end = g->mlx->win_height - 1;
	if (v->side == 0)
		r->wall_x = g->player.pos_y + v->perp_wall_dist * v->ray_dir_y;
	else
		r->wall_x = g->player.pos_x + v->perp_wall_dist * v->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEXTURE_WIDTH);
	if ((v->side == 0 && v->ray_dir_x > 0) || \
			(v->side == 1 && v->ray_dir_y < 0))
		r->tex_x = TEXTURE_WIDTH - r->tex_x - 1;
}

/* Function that choose the right texture to display depending of the hitted
 * wall and of the direction of the ray */
void	select_texture_and_draw(t_game *g, t_ray_params *r, t_ray_vars *v, \
		int x)
{
	int	texture_num;

	if (v->is_door)
		texture_num = get_door_texture(v);
	else
	{
		texture_num = 0;
		if (v->side == 0)
		{
			if (v->ray_dir_x < 0)
				texture_num = 2;
			else
				texture_num = 3;
		}
		else
		{
			if (v->ray_dir_y < 0)
				texture_num = 0;
			else
				texture_num = 1;
		}
	}
	draw_texture_line(g, texture_num, x, r);
}
