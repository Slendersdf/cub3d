/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:32:06 by fpaulas-          #+#    #+#             */
/*   Updated: 2025/04/18 11:08:24 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	handle_door_hit(t_ray_vars *v, t_game *g)
{
	int	door_index;

	v->hit = 1;
	v->is_door = 1;
	door_index = find_door_index(g, v->map_x, v->map_y);
	if (door_index != -1)
		v->d_open = g->doors[door_index].is_open;
	else
		v->d_open = 0;
}

int	get_door_texture(t_ray_vars *v)
{
	if (v->d_open)
		return (5);
	return (4);
}

/* Function that coordinates the work to calculate
* And display textured walls */
void	cast_ray(t_game *game, int x)
{
	t_ray_vars	vars;

	init_ray_vars(&vars, game, x);
	perform_dda(&vars, game);
	compute_wall_distance(&vars, game);
	calculate_ray_params(&vars.ray, &vars, game);
	select_texture_and_draw(game, &vars.ray, &vars, x);
}

/* Function to calculate the direction of the ray
* And initializes necessary fields */
void	init_ray_vars(t_ray_vars *v, t_game *g, int x)
{
	v->camera_x = 2 * x / (double)g->mlx->win_width - 1;
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
	v->is_door = 0;
	v->d_open = 0;
}
