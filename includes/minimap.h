/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/10 19:05:39 by ssabbaji         ###   ########.fr       */
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

#define MMAP_WALL_COLOR  0xFFFFFFFF
#define MMAP_EMPTY_COLOR 0xFF000000
#define PLAYER_COLOR 0xFF0000FF
#define OTHER_COL 0xFF1364CC
#define RAY_COLOR 0xE5FF7A
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
}               t_fcoord;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;


typedef struct s_coord
{
    int x;
    int y;
}               t_coord;

typedef struct s_player
{
    t_coord         map_pos;
    t_fcoord        world_pos;
    t_fcoord        dir; //direction of the player , vector of 1,0 if the ray is shot from his left for example
    t_fcoord        camera_plane;
}   t_player;

typedef struct s_map
{
    char        **map;
    int         height;
    int         width;
    char        *n_texture;
    char        *s_texture;
    char        *w_texture;
    char        *e_texture;
    t_rgb       floor;
    t_rgb       ceiling;
}   t_map; 


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
    double      euclid_dist;
    t_coord     step;
    int         side;
    int         hit;
}               t_raycast;

typedef struct s_text
{
    unsigned int     width;
    unsigned int     height;
    int     tex_x;
    int     tex_y;
    double  tex_pos;
    double  step;
    double  wall_x;
}   t_text;

typedef struct s_game_data
{
    t_map       *map;
    void        *mlx;
    t_player    player;
    mlx_image_t *img;
    t_raycast   raycast;
    double      perp_wall_dis;
    mlx_texture_t   *s_tex;
    mlx_texture_t   *n_tex;
    mlx_texture_t   *w_tex;
    mlx_texture_t   *e_tex;
    t_text      *text;
    int         tex_height;
    int         x;
    int         side;
    int         line_height;
    int         draw_start;
    int         draw_end;
    double      move_speed;
    double      rot_angle;
    int         screen_width;
    int         screen_height;
}   t_game_data;

/**********************-Functions**********************/


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
void        get_textures(t_game_data *game);
void        calculate_tex_infos(t_game_data *game, mlx_texture_t *tex);
void        draw_wall_text(t_game_data *game);
void        calculate_text_x(t_text *text, t_fcoord intersect);
double      find_wall_intersect(t_game_data *game);
void        draw_wall_text(t_game_data *game);
unsigned int	my_mlx_get_colour(mlx_texture_t *img, unsigned int x, unsigned int y);
void draw_line(t_game_data *game, int color);





#endif
