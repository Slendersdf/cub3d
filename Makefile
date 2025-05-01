# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 07:40:56 by caubert           #+#    #+#              #
#    Updated: 2025/04/18 12:54:57 by fpaulas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
NAME_BONUS = cub3D_bonus
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
MFLAGS	=	-Lminilibx -lmlx -lXext -lX11 -lm
RM		=	rm -f

SRCDIR	=	srcs
SRCDIR_BONUS = srcs_bonus
INCDIR	=	include
INCDIR_BONUS = include_bonus
OBJDIR	=	objs
OBJDIR_BONUS = objs_bonus
LIBDIR	=	libft

SRCS	=	main.c \
			cleanup/free_game.c cleanup/free_render.c cleanup/free_textures.c \
			cleanup/frees.c error/error.c parser/colors_utils.c \
			parser/dup_line.c parser/map_utils.c parser/parse_map.c \
			parser/parser.c parser/parser_utils.c parser/textures_utils.c \
			parser/validate_colors.c parser/validate_file.c \
			parser/validate_textures.c parser/validate_map.c \
			parser/map_parsing_utils.c setup/init_map.c setup/init_game.c \
			setup/init_mlx.c setup/init_player.c setup/init_render.c \
			setup/init_window.c window/hooks.c textures/load_textures.c \
			textures/render_textures.c textures/textures_utils.c \
			player/player_movement.c raycasting/raycaster.c \
			raycasting/raycaster_utils.c parser/validate_map_spaces.c \
			parser/empty_line_handler.c textures/textures_utils_2.c

SRCS_BONUS	=	main_bonus.c main_utils_bonus.c \
			cleanup/frees_bonus.c cleanup/free_game_bonus.c cleanup/free_render_bonus.c cleanup/free_textures_bonus.c \
			error/error_bonus.c \
			setup/init_map_bonus.c setup/init_game_bonus.c setup/init_mlx_bonus.c setup/init_player_bonus.c setup/init_render_bonus.c setup/init_window_bonus.c \
			parser/colors_utils_bonus.c parser/dup_line_bonus.c parser/map_utils_bonus.c \
			parser/parse_map_bonus.c parser/parser_bonus.c parser/parser_utils_bonus.c parser/textures_utils_bonus.c parser/validate_colors_bonus.c \
			parser/validate_file_bonus.c parser/validate_textures_bonus.c parser/validate_map_bonus.c parser/map_parsing_utils_bonus.c \
			window/hooks_bonus.c window/mouse_bonus.c \
			textures/load_textures_bonus.c textures/render_textures_bonus.c textures/textures_utils_bonus.c \
			player/player_movement_bonus.c \
			raycasting/raycaster_bonus.c raycasting/raycaster_utils_bonus.c \
			minimap/minimap_bonus.c parser/validate_map_spaces_bonus.c parser/empty_line_handler_bonus.c \
			window/door_bonus.c parser/doors_handler_bonus.c window/hooks_utils_bonus.c \
			textures/textures_utils_2_bonus.c whip/whip_bonus.c

OBJ		=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJDIR_BONUS)/, $(SRCS_BONUS:.c=.o))

LIBFT	=	$(LIBDIR)/libft.a

INC		=	-I$(INCDIR) -I$(LIBDIR)
INC_BONUS = -I$(INCDIR_BONUS) -I$(LIBDIR)

all:		$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	make -C minilibx
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MFLAGS) -o $(NAME)

$(NAME_BONUS):		$(LIBFT) $(OBJS_BONUS)
	make -C minilibx
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MFLAGS) -o $(NAME_BONUS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR_BONUS)/%.o:	$(SRCDIR_BONUS)/%.c | $(OBJDIR_BONUS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR_BONUS):
	mkdir -p $(OBJDIR_BONUS)

$(LIBFT):
	make -C $(LIBDIR)

bonus: $(LIBFT) $(NAME_BONUS)

clean:
	$(RM) -r $(OBJDIR) $(OBJDIR_BONUS)
	make -C $(LIBDIR) clean

fclean:			clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBDIR) fclean

re:		fclean all

.PHONY:	all clean bonus fclean re
