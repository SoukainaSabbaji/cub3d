# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 14:34:30 by ssabbaji          #+#    #+#              #
#    Updated: 2023/01/16 18:25:23 by ssabbaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map
CC = gcc
FLAGS = -Werror -Wextra -Wall -g

# Libraries for GLFW
LIBRARIES = -I include -lglfw -L "/Users/ssabbaji/.brew/opt/glfw/lib/"
MINILIBX = $(MINILIBX_DIRECTORY)libmlx42.a
MINILIBX_DIRECTORY = ./MLX42/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = minimap.c 

GREEN			=	"\033[1;32m"
PURPLE			=	"\x1b[35m"
RED				=  "\033[0;31m"

SRC = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJ = ${SRC:.c=.o}

%.o: %.c ./includes/minimap.h
	$(CC) $(FLAGS) -o $@ -c $< 

all: ${NAME}

${NAME}: ${MINILIBX} ${OBJ}
	$(CC) $(MINILIBX) $(OBJ) -o ${NAME} $(LIBRARIES) -fsanitize=address
	@echo $(GREEN) "Compilation done"

${MINILIBX}:
	@make -C $(MINILIBX_DIRECTORY)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(MINILIBX)
	$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@echo ${GREEN}"$(NAME) : nadafa mina l iman ..."

re: fclean all
