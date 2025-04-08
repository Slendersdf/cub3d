/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:50:10 by caubert           #+#    #+#             */
/*   Updated: 2025/04/08 16:32:42 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <minilibx/mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft.h"
# include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
}	t_mlx;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
}	t_textures;

typedef struct s_map
{
	t_textures	textures;
	char		**grid;
	int			height;
	int			width;
	int			parsing_map;
}	t_map;

typedef struct s_game
{
	t_map	*map;
	t_mlx	*mlx;
}	t_game;

typedef struct s_ray_params
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	wall_x;
}	t_ray_params;

// Structure pour les directions du raycasting
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

// Structure pour chaque texture chargee avec MiniLibX
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_texture;

// Structure pour l'image dans laquelle on dessine chaque frame
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

// Structure pour appeler les autres structures
typedef struct s_game
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	player;
	t_img		img;
	t_texture	textures[4]; // 0 = NO, 1 = SO, 2 = WE, 3 = EA
}	t_game;

int		main(int argc, char **argv);


int		init_window(t_game *game);
t_game	*init_game(void);
t_mlx	*init_mlx_struct(void);
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
void	free_game(t_game *game);
int		setup_hooks(t_game *game);
void	free_game(t_game *game);

int		handle_close(t_game *game);
int		handle_keypress(int keycode, t_game *game);



/*setup*/
t_map	*init_map(void);

/*cleanup*/
void	free_map(t_map *map);

/*parsing*/
int		parse_color(char *line, int *color);
int		parse_texture(char *line, char **texture);

int		validate_file(char *filename);
int		validate_map_spaces(t_map *map);
int		validate_texture_path(char *path);
int		is_valid_number(char *str);

int		read_file_content(int fd, t_map *map);
int		process_line(char *line, int type, t_map *map);
int		parse_map_line(char *line, t_map *map);
int		finalize_map_parsing(t_map *map);
int		check_player_position(t_map *map);

int		error_msg(char *msg);
int		error_msg_free(char *msg, void *ptr);
void	free_grid(char **grid, int height);

void	free_map(t_map *map);
void	free_split(char **split);
void	free_gnl_buffer(int fd);

int		is_valid_map_line(char *line);
int		check_trailing_chars(char *line);
int		is_map_line(char *line);

char	*dup_line_with_spaces(char *line);
int		get_line_type(char *line);
int		check_all_elements_loaded(t_map *map);

int		check_initial_comma(char *line);
int		check_consecutive_commas(char *str);
int		check_trailing_comma(char *str);

int		check_texture_extension(char *path);
char	*extract_texture_path(char *line, int start);
int		validate_texture_identifier(char *line, int *i);

int		check_valid_chars(char c);
int		is_empty_or_spaces(char *line);

int		verify_map_content(t_map *map);
int		verify_map_started(t_map *map);
int		validate_map_format(t_map *map);

#endif
