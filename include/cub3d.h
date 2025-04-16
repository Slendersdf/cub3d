/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 07:50:10 by caubert           #+#    #+#             */
/*   Updated: 2025/04/16 14:29:42 by fpaulas-         ###   ########.fr       */
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
# include <../minilibx/mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "libft.h"

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define MINIMAP_SCALE 8

#define WHIP_FRAME_COUNT 6

extern char *whip_frame_paths[WHIP_FRAME_COUNT];
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
}	t_mlx;

/* Used to store a MLX image. */
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}	t_img;

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
}	t_keys;

/* Used for player position, rotation and movements. */
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rotation_speed;
}	t_player;

/* Used for raycasting parameters. */
typedef struct s_ray_params
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			wall_x;
}	t_ray_params;

typedef struct s_ray_vars
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	t_ray_params	ray;
}	t_ray_vars;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
	//char			*one;
	//char			*two;
}	t_textures;

typedef struct s_map
{
	t_textures		textures;
	char			**grid;
	int				height;
	int				width;
	int				parsing_map;
}	t_map;

typedef struct s_whip
{
	t_img	**frames;
	int		frame_count;
	int		current_frame;
	int		is_active;
	int		*frame_delay; // nombre de frames a attendre entre deux images
	int		current_delay; // compteur actuel
}	t_whip;

typedef struct s_game
{
	t_map			*map;
	t_mlx			*mlx;
	t_img			**textures;
	t_img			*screen;
	int				floor_color;
	int				ceiling_color;
	t_player		player;
	t_keys			keys;
	int				mouse_captured;
	t_whip			whip;
}	t_game;

int				handle_keyrelease(int keycode, t_game *game);

int				main(int argc, char **argv);

int				init_window(t_game *game);
t_game			*init_game(void);
t_mlx			*init_mlx_struct(void);
int				handle_keypress(int keycode, t_game *game);
int				handle_close(t_game *game);
void			free_game(t_game *game);
int				setup_hooks(t_game *game);
void			free_game(t_game *game);
int				handle_mouse_move(int x, int y, t_game *game);
void			toggle_mouse_capture(t_game *game);

int				handle_close(t_game *game);
int				handle_keypress(int keycode, t_game *game);

/*Textures*/
int				load_textures(t_game *game);
t_img			*load_texture_file(t_game *game, char *path);
void			free_all_textures(t_game *game);
void			free_texture(t_mlx *mlx, t_img *texture);
int				create_rgb(int r, int g, int b);
unsigned int	get_pixel_color(t_img *img, int x, int y);
void			put_pixel_to_img(t_img *img, int x, int y, unsigned int color);
t_img			*create_new_image(t_mlx *mlx, int width, int height);
void			fill_image(t_img *img, unsigned int color);
void			draw_texture_line(t_game *game, int texture_num, int x, \
					t_ray_params *params);

/*Player*/
void			init_player(t_game *game);
void			init_player_direction(t_game *game, char orientation);
void			move_player_forward(t_game *game, double move_speed);
void			move_player_sideways(t_game *game, double move_speed);
void			rotate_player(t_game *game, double rotation_speed);

/*Rendering*/
int				init_render(t_game *game);
int				render_frame(t_game *game);
void			free_render(t_game *game);

/*Raycasting*/
void			cast_ray(t_game *game, int x);
void			init_ray_vars(t_ray_vars *v, t_game *g, int x);
void			init_step_and_side(t_ray_vars *v, t_game *g);
void			perform_dda(t_ray_vars *v, t_game *g);
void			compute_wall_distance(t_ray_vars *v, t_game *g);
void			calculate_ray_params(t_ray_params *r, t_ray_vars *v, t_game *g);
void			select_texture_and_draw(t_game *g, t_ray_params *r, \
					t_ray_vars *v, int x);

/*setup*/
t_map			*init_map(void);

/*cleanup*/
void			free_map(t_map *map);

/*parsing*/
int				parse_color(char *line, int *color);
int				parse_texture(char *line, char **texture);

int				validate_file(char *filename);
int				validate_map_spaces(t_map *map);
int				validate_texture_path(char *path);
int				is_valid_number(char *str);

int				read_file_content(int fd, t_map *map);
int				process_line(char *line, int type, t_map *map);
int				parse_map_line(char *line, t_map *map);
int				finalize_map_parsing(t_map *map);
int				check_player_position(t_map *map);

int				error_msg(char *msg);
int				error_msg_free(char *msg, void *ptr);
void			free_grid(char **grid, int height);

void			free_map(t_map *map);
void			free_split(char **split);
void			free_gnl_buffer(int fd);

int				is_valid_map_line(char *line);
int				check_trailing_chars(char *line);
int				is_map_line(char *line);

char			*dup_line_with_spaces(char *line);
int				get_line_type(char *line);
int				check_all_elements_loaded(t_map *map);

int				check_initial_comma(char *line);
int				check_consecutive_commas(char *str);
int				check_trailing_comma(char *str);

int				check_texture_extension(char *path);
char			*extract_texture_path(char *line, int start);
int				validate_texture_identifier(char *line, int *i);

int				check_valid_chars(char c);
int				is_empty_or_spaces(char *line);

int				verify_map_content(t_map *map);
int				verify_map_started(t_map *map);
int				validate_map_format(t_map *map);

//BONUS//

/*minimap*/
void	draw_square(t_img *img, int x, int y, int size, int color);
void	draw_player_on_minimap(t_game *game, int offset_x, int offset_y);
void	draw_minimap(t_game *game);

/*sprite WHIP*/
void	init_whip(t_game *game);
void	update_whip(t_game *game);
void	draw_whip_frame(t_game *game, t_img *frame);
int		mouse_press(int button, int x, int y, t_game *game);

#endif
