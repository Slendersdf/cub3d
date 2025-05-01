/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:51:32 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 17:51:32 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Inits the mlx structure along with window's dimentions. */
t_mlx	*init_mlx_struct(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->win_width = 1024;
	mlx->win_height = 768;
	return (mlx);
}
