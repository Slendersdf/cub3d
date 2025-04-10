/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:19:49 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/10 17:56:32 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that runs through each x columns (left to right)
// And send a ray in the world for each of them
void	render_frame(t_games *games)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_ray(games, x);
		x++;
	}
}

// Function that coordinates the work to calculate
// And display textured walls
void	cast_ray(t_games *games, int x)
{
	t_ray_vars	vars;

	init_ray_vars(&vars, games, x);
	perform_dda(&vars, games);
	compute_wall_distance(&vars, games);
	calculate_ray_params(&vars.ray, &vars, games);
	select_texture_and_draw(games, &vars.ray, &vars, x);
}

// Function to calculate the direction of the ray
// And initializes necessary fields
void	init_ray_vars(t_ray_vars *v, t_games *g, int x)
{
	v->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	v->ray_dir_x = g->player.dir_x + g->player.plane_x * v->camera_x;
	v->ray_dir_y = g->player.dir_y + g->player.plane_y * v->camera_x;
	v->map_x = (int)g->player.pos_x;
	v->map_y = (int)g->player.pos_y;
	if (v->ray_dir_x == 0)
		v->delta_dist_x = 1e30;
	else
		v->delta_dist_x = fabs(1 / v->ray_dir_x);
	if (v->ray_dir_y == 0)
		v->delta_dist_y = 1e30;
	else
		v->delta_dist_y = fabs(1 / v->ray_dir_y);
	init_step_and_side(v, g);
	v->hit = 0;
	v->side = 0;
}

// Function to define in which direction we will jump in the grid
// It also calculate the distance between player and first line or column
void	init_step_and_side(t_ray_vars *v, t_games *g)
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

// Function that uses DDA (Digitial Differential Analyzer) algorthim
// To run through the map until a wall is found (hit)
void	perform_dda(t_ray_vars *v, t_games *g)
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
	}
}

// Function that calculates the exact distance between player and a wall
// after the player hits a wall
void	compute_wall_distance(t_ray_vars *v, t_games *g)
{
	if (v->side == 0)
		v->perp_wall_dist = (v->map_x - g->player.pos_x +
				(1 - v->step_x) / 2.0) / v->ray_dir_x;
	else
		v->perp_wall_dist = (v->map_y - g->player.pos_y +
				(1 - v->step_y) / 2.0) / v->ray_dir_y;
}

// Function that calculates height and vertical position of the wall displayed
void	calculate_ray_params(t_ray_params *r, t_ray_vars *v, t_games *g)
{
	r->line_height = (int)(SCREEN_HEIGHT / v->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	if (v->side == 0)
		r->wall_x = g->player.pos_y + v->perp_wall_dist * v->ray_dir_y;
	else
		r->wall_x = g->player.pos_x + v->perp_wall_dist * v->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEXTURE_WIDTH);
	if ((v->side == 0 && v->ray_dir_x > 0) || (v->side == 1 && v->ray_dir_y < 0))
		r->tex_x = TEXTURE_WIDTH - r->tex_x - 1;
}

// Function that choose the right texture to display depending of the hitted wall
// And of the direction of the ray
void	select_texture_and_draw(t_games *g, t_ray_params *r, t_ray_vars *v, int x)
{
	t_texture	*tex;

	tex = NULL;
	if (v->side == 0)
	{
		if (v->ray_dir_x < 0)
			tex = &g->textures[2]; // WE
		else
			tex = &g->textures[3]; // EA
	}
	else
	{
		if (v->ray_dir_y < 0)
			tex = &g->textures[0]; // NO
		else
			tex = &g->textures[1]; // SO
	}
	draw_vertical_line(g, x, r, tex);
}
