# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 14:34:30 by ssabbaji          #+#    #+#              #
#    Updated: 2023/02/23 18:34:43 by ssabbaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = cub3D
CC = gcc
FLAGS = -Werror -Wextra -Wall -g

ifeq ($(shell uname), Darwin)
	LIBRARIES = -I include -lglfw -L "/Users/ssabbaji/.brew/opt/glfw/lib/"
else
	LIBRARIES = -ldl -lglfw3 -pthread -lm -I ./includes/minimap.h
endif
MINILIBX = $(MINILIBX_DIRECTORY)libmlx42.a libft/libft.a
MINILIBX_DIRECTORY = ./MLX42/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = parsing.c main.c lodev.c drawing.c hooks.c helper.c minimap.c ft_check_input.c \
				ft_getmap.c ft_check_line.c ft_check_map2d.c ft_check_player.c init_calc_vars.c \
				perform_dda.c initialize_game_vars.c start_game.c\
				ft_getcolors.c ft_getelem.c ft_getpath.c ft_getrgb.c \


################################################################################
#                                  Makefile  objs                              #
################################################################################

GREEN			=	"\033[1;32m"
PURPLE			=	"\x1b[35m"
RED				=  "\033[0;31m"

SRC = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJ = ${SRC:.c=.o}

%.o: %.c ./includes/minimap.h
	$(CC) $(FLAGS) -o $@ -c $< 

all:	${NAME}

${NAME}: ${MINILIBX} ${OBJ}
	@make -C ./libft
	$(CC) $(MINILIBX) $(OBJ) -o ${NAME} $(LIBRARIES)
	@echo $(GREEN) "Compilation done"

${MINILIBX}:
	@make -C $(MINILIBX_DIRECTORY)

clean:
	rm -rf $(OBJ)
	@make clean -C ./libft

fclean: clean
	rm -rf $(NAME) $(MINILIBX)
	$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@make fclean -C ./libft
	@echo ${GREEN}"$(NAME) : nadafa mina l iman ..."

re: fclean all