/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/10 10:00:00 by ssabbaji         ###   ########.fr       */
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
#define OTHER_COL 0xCC1436
// #define RAY_COLOR 0xE5FF7A
#define RAY_COLOR 0xE5FF7A
#define PI 3.14159265359
#define WALL '1'
#define EMPTY '0'
#define STRAFE_SPEED 0.1

extern int color;

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
    t_fcoord        camera_plane;
    t_fcoord        current_ray;
    mlx_image_t     *img;
    float           rot_angle;
    float           fov;
}   t_player;


typedef struct s_image
{
    void    *img_ptr;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;
}   t_image;
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

typedef struct s_raycast
{
    t_fcoord    ray_dir;
    t_fcoord    side_dist;
    t_fcoord    delta_dist;
    t_coord     step;
    int         side;
    int         hit;
}               t_raycast;

typedef struct s_text
{
    void    *img_ptr;
    int     width;
    int     height;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;
    mlx_texture_t   *s_tex;
    mlx_texture_t   *n_tex;
    mlx_texture_t   *w_tex;
    mlx_texture_t   *e_tex;

    
}   t_text;

typedef struct s_game_data
{
    t_map       *map;
    void        *mlx;
    t_player    player;
    t_wall      *wall;
    t_cube      *cube;
    mlx_image_t *img;
    t_image     *image;
    t_raycast   raycast;
    t_fcoord    pos; //position of the player in the world
    double      time;
    double      old_time;
    double      perp_wall_dis;
    t_text      *text;
    int         x;
    int         side;
    int         line_height;
    int         draw_start;
    int         draw_end;
    double      move_speed;
    double      rot_angle;
    double      frame_time;
    int         screen_width;
    int         screen_height;
    char        start_dir;
}   t_game_data;

/**********************-Functions**********************/
void    get_map_dims(t_map *map);

void draw_player(t_coord pos, t_coord mini_map_size, int size);


void hook_2(void *param);
void hook(void *param);

t_coord *draw_square(t_coord *points,mlx_image_t *img, t_coord pos, t_coord dims, int color, int size);
void    draw_line(t_game_data *game, int color);
// void draw_line(t_coord p1, t_coord p2, int color ,mlx_image_t *img);
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
int	    ft_getnbrof_lines(char *file_name);


/******************* - teh fun stuff - *******************/
void        drawing_calc(t_game_data *game);
void        init_game_dir(t_player *player, char start_dir);
void        ready_start(void *ptr);
void        start_drawing(t_game_data *game);
void        init_pregame_parse(t_game_data *game, char **argv);
void        init_map(t_game_data *game);
void        init_player(t_game_data *game);
void        init_game_vars(t_game_data *game);
void        start_dda(t_raycast *raycast, t_map *map, t_coord start_pos);
void        calculate_line_height(t_game_data *data);
void        draw_floor_ceiling(t_game_data *game);
void        draw_rectangles(mlx_image_t *img, t_coord pos, t_coord dims, unsigned int color);
unsigned int         conv_rgb(t_rgb color);
int         ft_getnbrof_cols(char **map);
float       vector_size(t_fcoord coord);
t_fcoord    normalize_vector(t_fcoord vector);
int         valid_coord(t_coord coord, t_map *map);
t_coord     get_coord(int x, int y);
void        call_hooks();
void        esc_keyhook(mlx_key_data_t data, void *param);
void        handle_input(void *param);
double      calculate_perp(t_raycast raycast);
t_fcoord    scale_vector(t_fcoord vector, float scalar);
t_fcoord    add_vector(t_fcoord vector1, t_fcoord vector2);
void        init_raycast(t_raycast *raycast, t_player *player, t_fcoord ray_dir);

// void glfw_clear_window(GLFWwindow* window)
// {
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);
//     glClear(GL_COLOR_BUFFER_BIT);
// }


mlx_image_t *g_img;//replaced by game->cube->img
mlx_image_t *g_player_img; //wouldnt need this after moving to a 3D engine
mlx_t *g_mlx; // replaced by game->cube->mlx
t_player *g_player; //replaced by game->player
t_wall *g_wall;
t_map *g_map;
t_game_data *g_game;

#endif
