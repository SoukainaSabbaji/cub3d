# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 13:28:41 by ssabbaji          #+#    #+#              #
#    Updated: 2023/01/12 18:06:19 by ssabbaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = map
CC = gcc
FLAGS = -W -W -W
LIBRARIES = -lmlx -lm -framework OpenGL -framework AppKit

MINILIBX = $(MINILIBX_DIRECTORY)libmlxa.a
MINILIBX_DIRECTORY = ./minilibx/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = minimap.c 

GREEN			=	"\033[1;32m"
PURPLE			=	"\x1b[35m"
RED				=  "\033[0;31m"

SRC = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

%.o: %.c ./includes/minimap.h
	$(CC) $(FLAGS) -o $@ -c $< 

all: ${NAME}

${NAME}: ${OBJ} ${MINILIBX}
	$(CC) $(FLAGS) $(OBJ) -o ${NAME} $(LIBRARIES) -I $(MINILIBX_HEADERS) -fsanitize=address
	@echo ${PURPLE}"$(NAME): Compiling"

$(MINILIBX):
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)
	@echo ${PURPLE}"$(NAME): creating mlx"

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	@echo ${GREEN}"$(NAME) : nadafa mina l iman ..."

re: fclean all