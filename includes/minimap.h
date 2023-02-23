/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:35 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/23 12:19:05 by ssabbaji         ###   ########.fr       */
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

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

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

typedef struct s_player
{
    t_coord         map_pos;
    t_fcoord        world_pos;
    t_fcoord        dir; //direction of the player , vector of 1,0 if the ray is shot from his left for example
    mlx_image_t     *img;
    t_coord         camera_plane;
    float           rot_angle;
    float           fov;
    
}   t_player;

typedef struct s_map
{
    char        **map;
    FILE        *map_file;
    int         height;
    int         width;
    char        *n_texture;
    char        *s_texture;
    char        *w_texture;
    char        *e_texture;
    t_rgb       floor;
    t_rgb       ceiling;
    int         nbr_of_walls;
    // t_player    *player;
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

typedef struct s_game_data
{
    t_map       *map;
    t_player    *player;
    t_wall      *wall;
    t_ray       *ray;
    t_cube      *cube;
    mlx_image_t *img;
    t_fcoord    camera_plane;
    t_fcoord    ray_dir;
    t_fcoord    plane;
    t_fcoord    pos; //position of the player in the world
    double      time;
    double      old_time;
    t_coord     map_pos;
    t_fcoord    side_dist;
    t_fcoord    delta_dist;
    double      perp_wall_dist;
    t_coord     step;
    int         x;
    int         hit;
    int         side;
    int         line_height;
    int         draw_start;
    int         draw_end;
    double      move_speed;
    double      rot_angle;
    double      frame_time;
    int         screeen_width;
    int         screeen_height;
    char        start_dir;
}   t_game_data;

/**********************-Functions**********************/
void    get_map_dims(t_map *map);

void draw_player(t_coord pos, t_coord mini_map_size, int size);


void hook_2(void *param);
void hook(void *param);

t_coord *draw_square(t_coord *points,mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);
void    draw_line(t_coord p1, t_coord p2, int color, t_coord dims);
void	ft_drawline(t_coord p1, t_coord p2, int color);
void    draw_circle(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);
void    draw_square_2(t_coord *points, mlx_image_t *img, int color, int size);

void	move_player(t_fcoord move);

int		count_walls(FILE *mapFile);

void	ft_error(void);
int		min(int a, int b);
void	print_map_array(t_map *map);
void	ft_check_input(int nbr_of_args, char **args);
char	**ft_getmap2d(char *map_path);
void    draw_map(mlx_t *mlx, t_map *map, t_coord mini_map_size);
void	ft_check_first_line(char **table);
void	ft_check_last_line(char **table);
void	ft_check_frst_lst_char(char **table);
void	ft_check_top_down(char **table);
void	ft_check_left_right(char **table);
int		ft_count_nbrof_player(char **table);
void	ft_check_nbrof_players(char **table);
void	ft_check_player_position(char **table);
void	ft_check_player(char **table);
void	ft_check_map2d(char **map2d);
t_map	*ft_getmap(char *map_filename);
char	*ft_getpath(char	*file_name, char *direction);
t_rgb	ft_getrgb(char *file_name, char *f_c);
t_rgb	ft_rgberr(void);
t_rgb	ft_getcolors(char *str);
int		ft_2darrlen(char **arr);
void	ft_free2darr(char **arr);



/******************* - teh fun stuff - *******************/
void    drawing_calc(t_game_data *game);
void    calculate_step(t_game_data *game);
void    init_game_dir(t_game_data *game);
void    ready_start(void *ptr);
void    start_drawing(t_game_data *game);
void    init_pregame_parse(t_game_data *game);
void    init_map(t_game_data *game);
void    init_player(t_game_data *game);
void    init_game_vars(t_game_data *game);
void    init_dda(t_game_data *data);
void    calculate_line_height(t_game_data *data);


mlx_image_t *g_img;//replaced by game->cube->img
mlx_image_t *g_player_img; //wouldnt need this after moving to a 3D engine
mlx_t *g_mlx; // replaced by game->cube->mlx
t_player *g_player; //replaced by game->player
t_wall *g_wall;
t_map *g_map;

#endif