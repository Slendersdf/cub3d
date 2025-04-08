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

int	main(int argc, char **argv)
{
	t_game	*game;

	if (!check_args(argc, argv))
		return (1);
	game = init_game();
	if (!game)
		return (error_msg("Game initialization failed"));
	if (!validate_file(argv[1]))
	{
		free_game(game);
		return (1);
	}
	game->map = parse_file(argv[1]);
	if (!game->map || !init_window(game))
	{
		free_game(game);
		return (1);
	}
	setup_hooks(game);
	mlx_loop(game->mlx->mlx);
	free_game(game);
	return (0);
}
