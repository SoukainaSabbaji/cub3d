/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:35 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/17 11:38:10 by ssabbaji         ###   ########.fr       */
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
#include <errno.h>
#include <fcntl.h>
#include "math.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"

#define WALL_SIZE 64
#define PLAYER_SIZE 16 
#define PLAYER_RATIO PLAYER_SIZE / WALL_SIZE
#define MMAP_WALL_COLOR  0xFFFFFFFF
#define MMAP_EMPTY_COLOR 0xFF000000
#define PLAYER_COLOR 0xFF0000FF
// #define RAY_COLOR 0xE5FF7A
#define RAY_COLOR 0xE5FF7A
#define PI 3.14159265359


typedef struct s_fcoord
{
    float x;
    float y;
    // float dx;
    // float dy;
}               t_fcoord;

typedef struct s_cord
{
    int d;
    int error;
    int slope;
}               t_cord;

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
    t_fcoord    dir; //direction of the player , vector of 1,0 if the ray is shot from his left for example
    mlx_image_t *img;
    t_coord    camera_plane;
    float      rot_angle;
    float      fov;
    
}   t_player;


typedef struct s_iter
{
    int i;
    int j;
    int k;
}   t_iter;

typedef struct s_ray
{
    t_fcoord    ray_dir; //direction of the ray in world space matches the player's direction
    t_fcoord    ray_origin; //origin of the ray in world space matches the player's position
    // t_coord     step; //step to take in the map
}   t_ray;

/**********************-Functions**********************/
void    get_map_dims(FILE *mapFile, t_map *map);

void draw_player(t_coord pos, t_coord mini_map_size, int size);


void hook_2(void *param);
void hook(void *param);

t_coord *draw_square(t_coord *points,mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);
void    draw_line(t_coord p1, t_coord p2, int color, t_coord dims);
void	ft_drawline(t_coord p1, t_coord p2, int color);
void    draw_circle(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);
void    draw_square_2(t_coord *points, mlx_image_t *img, int color, int size);

void move_player(t_fcoord move);

int count_walls(FILE *mapFile);

void ft_error(void);
int min(int a, int b);
t_map *get_map(char *map_path);
void print_map_array(t_map *map);
void draw_map(mlx_t *mlx, t_map *map, t_coord mini_map_size);
void    ft_check_input(int nbr_of_args, char **args);




mlx_image_t *g_img;
mlx_image_t *g_player_img;
mlx_t *g_mlx;
t_player *g_player;
t_wall *g_wall;
t_map *g_map;

#endif