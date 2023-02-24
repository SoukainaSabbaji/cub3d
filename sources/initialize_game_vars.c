/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:55:31 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/24 14:32:09 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    init_game_vars(t_game_data *game)
{
    //posx and posy start position are the same as the position of the player in the map
    game->pos.x = game->player->world_pos.x;
    game->pos.y = game->player->world_pos.y;
    game->time = 0;
    game->old_time = 0;
    game->move_speed = 0.3;
    game->rot_angle = 0.2;
    init_game_dir(game);
}

void    init_player(t_game_data *game)
{
    game->player->world_pos.x = 0;
    game->player->world_pos.y = 0;
    game->player->dir.x = 0;
    game->player->dir.y = 0;
    //are the dir variables the same as the ray_dir variables ?
    //i literally have no idea
}

void    init_map(t_game_data *game)
{
    game->map->e_texture = NULL;
    game->map->n_texture = NULL;
    game->map->s_texture = NULL;
    game->map->w_texture = NULL;
    game->map->map = NULL;
    // get_map_dims(game->map);// placeholder for the new func
}

void    init_pregame_parse(t_game_data *game)
{
    init_map(game);
    // init_player(game);
    game->screen_height = 480;
    game->screen_width = 640;
    // game->image->img_data
    // game->cube->win = mlx_new_window(game->cube->mlx, game->screen_width, game->screen_height, "minimap");
    // game->img->pixels = (int *)mlx_get_data_addr(game->image->img_ptr, &game->image->bpp, &game->image->size_line, &game->image->endian); 
}

/* steps to follow */
// 1. init_pregane_parse
// 2. init_game_vars
// 3. make a function that starts the game and put it in the mlx_loop_hook
