/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:35 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/31 12:58:27 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#define WALL '1'
#define EMPTY '0'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
    char   **map;
    int     height;
    int     width;
}   t_map; 

typedef struct s_cube
{
    void    *mlx;
    void    *win;
    t_map   *map;
    char    *img_data;
    void    *img_ptr;
    int     bpp;
    int     line_size;
    int     endian;
}   t_cube;

typedef struct s_wall
{
    int x;
    int y;
}   t_wall;

typedef struct s_player
{
    int         x;
    int         y;
    mlx_image_t *img;
}   t_player;


typedef struct s_iter
{
    int i;
    int j;
}   t_iter;



/**********************-Functions**********************/
void    get_map_dims(FILE *mapFile, t_map *map);


#endif