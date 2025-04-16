/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:50:41 by caubert           #+#    #+#             */
/*   Updated: 2025/02/08 14:50:41 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		return (0);
	}
	return (1);
}

int	game_loop(t_game *game)
{
	if (game->keys.w)
		move_player_forward(game, game->player.move_speed);
	if (game->keys.s)
		move_player_forward(game, -game->player.move_speed);
	if (game->keys.a)
		move_player_sideways(game, -game->player.move_speed);
	if (game->keys.d)
		move_player_sideways(game, game->player.move_speed);
	if (game->keys.left)
		rotate_player(game, -game->player.rotation_speed);
	if (game->keys.right)
		rotate_player(game, game->player.rotation_speed);
	handle_door_interaction(game);
	render_frame(game);
	return (0);
}

/*Initializes map structure and parsing/verification processes in /parser.*/
static t_map	*parse_file(char *filename)
{
	t_map	*map;
	int		fd;
	int		ret;

	map = init_map();
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		return (NULL);
	}
	ret = read_file_content(fd, map);
	close(fd);
	if (!ret || !finalize_map_parsing(map))
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}

static int	setup_game(t_game **game, char *map_path)
{
	*game = init_game();
	if (!*game)
		return (error_msg("Game initialization failed"));
	if (!validate_file(map_path))
	{
		free_game(*game);
		return (0);
	}
	(*game)->map = parse_file(map_path);
	if (!(*game)->map)
	{
		free_game(*game);
		return (0);
	}
	if (!setup_graphics(*game))
	{
		free_game(*game);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!check_args(argc, argv))
		return (1);
	if (!setup_game(&game, argv[1]))
		return (1);
	mlx_loop_hook(game->mlx->mlx, game_loop, game);
	mlx_loop(game->mlx->mlx);
	free_game(game);
	return (0);
}
