# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 14:34:30 by ssabbaji          #+#    #+#              #
#    Updated: 2023/03/06 08:46:35 by ssabbaji         ###   ########.fr        #
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
MINILIBX = $(MINILIBX_DIRECTORY)libmlx42.a
LIBFT = $(LIBFT_DIRECTORY)libft.a
MINILIBX_DIRECTORY = ./MLX42/
LIBFT_DIRECTORY = ./libft/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

SOURCES_DIRECTORY = ./sources/

PARSING = ft_getmap.c ft_check_line.c ft_check_map2d.c ft_check_player.c \
		  ft_getcolors.c ft_getelem.c ft_getpath.c ft_getrgb.c ft_check_input.c 
SOURCES_LIST = parsing.c main.c lodev.c drawing.c hooks.c helper.c \
			   init_calc_vars.c vector_utils.c coord_utils.c\
			   perform_dda.c initialize_game_vars.c start_game.c\
			   $(addprefix parsing/, $(PARSING))


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

${NAME}: ${MINILIBX} ${OBJ} ${LIBFT}
	$(CC) $(MINILIBX) $(OBJ) ${LIBFT} -o ${NAME} $(LIBRARIES) -fsanitize=address 
	@echo $(GREEN) "Compilation done"

${MINILIBX}:
	@make -C $(MINILIBX_DIRECTORY)

${LIBFT}: 
	@make -C $(LIBFT_DIRECTORY)

clean:
	rm -rf $(OBJ)
	@make clean -C ./libft

fclean: clean
	rm -rf $(NAME) $(MINILIBX) $(LIBFT)
	$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@echo ${GREEN}"$(NAME) : nadafa mina l iman ..."

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re