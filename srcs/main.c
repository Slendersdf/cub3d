/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:50:41 by caubert           #+#    #+#             */
/*   Updated: 2025/04/09 15:59:54 by fpaulas-         ###   ########.fr       */
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

/* int	main(int argc, char **argv)
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
} */

int	game_loop(t_games *games)
{
	render_frame(games);
	mlx_put_image_to_window(games->mlx->mlx, games->mlx->win, games->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_games	games;

	if (!check_args(argc, argv))
		return (1);

	games.map = parse_file(argv[1]);
	if (!games.map)
		return (1);

	games.mlx = malloc(sizeof(t_mlx));
	if (!games.mlx)
		return (1);

	games.mlx->mlx = mlx_init();
	games.mlx->win = mlx_new_window(games.mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	games.mlx->win_width = SCREEN_WIDTH;
	games.mlx->win_height = SCREEN_HEIGHT;

	if (init_image(&games))
		return (1);

	if (load_textures(&games)) // fonction de ton mate
		return (1);

	init_player(&games);

	mlx_loop_hook(games.mlx->mlx, game_loop, &games);
	mlx_loop(games.mlx->mlx);

	return (0);
}
