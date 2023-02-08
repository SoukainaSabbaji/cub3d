/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:35 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/07 17:43:42 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#define WALL '1'
#define EMPTY '0'
#define PLAYER 'P'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "math.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define WALL_SIZE 64
#define PLAYER_SIZE 16 
#define PLAYER_RATIO PLAYER_SIZE / WALL_SIZE
#define MMAP_WALL_COLOR  0xFFFFFFFF
#define PLAYER_COLOR 0xFF0000FF
#define PI 3.14159265359



typedef struct s_fcoord
{
    float x;
    float y;
    // float dx;
    // float dy;
}               t_fcoord;

typedef struct s_coord
{
    int x;
    int y;
    // int dx;
    // int dy;
}               t_coord;


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
    t_coord     map_pos;
    t_fcoord    world_pos;
    t_fcoord    dir;
    mlx_image_t *img;
    float      rot_angle;
    float      fov;
    
}   t_player;


typedef struct s_iter
{
    int i;
    int j;
    int k;
}   t_iter;



/**********************-Functions**********************/
void    get_map_dims(FILE *mapFile, t_map *map);

void draw_player(int color, t_coord pos, t_coord mini_map_size, int size);

void    draw_square(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);

#endif