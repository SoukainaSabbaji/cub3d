# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 14:34:30 by ssabbaji          #+#    #+#              #
#    Updated: 2023/01/16 14:34:33 by ssabbaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map
CC = gcc
FLAGS = -W -W -W 

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
	$(CC) $(MINILIBX) $(OBJ) -o ${NAME} $(LIBRARIES)
	@echo $(GREEN) "Compilation done"

${MINILIBX}:
	@make -C $(MINILIBX_DIRECTORY)

clean:
	@rm -f ${OBJ}
	@make clean -C $(MINILIBX_DIRECTORY)
	@echo $(RED) "Clean done"

fclean: clean
	@rm -f ${NAME}
	@make fclean -C $(MINILIBX_DIRECTORY)
	@echo $(RED) "Fclean done"

re: fclean all

