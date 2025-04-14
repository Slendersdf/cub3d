# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 07:40:56 by caubert           #+#    #+#              #
#    Updated: 2025/04/14 15:50:26 by fpaulas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
MFLAGS	=	-Lminilibx -lmlx -lXext -lX11 -lm
RM		=	rm -f

SRCDIR	=	srcs
INCDIR	=	include
OBJDIR	=	objs
LIBDIR	=	libft

SRCS	=	main.c \
			cleanup/frees.c cleanup/free_game.c cleanup/free_render.c cleanup/free_textures.c \
			error/error.c \
			setup/init_map.c setup/init_game.c setup/init_mlx.c setup/init_player.c setup/init_render.c setup/init_window.c \
			parser/colors_utils.c parser/dup_line.c parser/map_utils.c \
			parser/parse_map.c parser/parser.c parser/parser_utils.c parser/textures_utils.c parser/validate_colors.c \
			parser/validate_file.c parser/validate_textures.c parser/validate_map.c parser/map_parsing_utils.c \
			window/hooks.c window/mouse.c \
			textures/load_textures.c textures/render_textures.c textures/textures_utils.c \
			player/player_movement.c \
			raycasting/raycaster.c raycasting/raycaster_utils.c \
			minimap/minimap.c

OBJ		=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT	=	$(LIBDIR)/libft.a

INC		=	-I$(INCDIR) -I$(LIBDIR)

all:		$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MFLAGS) -o $(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)
	make -C $(LIBDIR) clean

fclean:			clean
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re:		fclean all

.PHONY:	all clean fclean re
