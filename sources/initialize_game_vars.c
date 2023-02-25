/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:55:31 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/25 14:00:55 by ssabbaji         ###   ########.fr       */
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

void    find_player_pos(t_game_data *game)
{
    //iterate through the map array and find the position of the player
    
    t_map *map = game->map;
    int i = 0;
    int j = 0;
    while (i < map->height)
    {
        while (j < map->width)
        {
            if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
            {
                game->player->world_pos.x = j;
                game->player->world_pos.y = i;
                printf("player pos: %f, %f\n", game->player->world_pos.x, game->player->world_pos.y);
                return ;
            }
            j++;
        }
        j = 0;
        i++;
    }
}

void    init_player(t_game_data *game)
{
    find_player_pos(game);
}

void    init_map(t_game_data *game)
{
    game->map->e_texture = NULL;
    game->map->n_texture = NULL;
    game->map->s_texture = NULL;
    game->map->w_texture = NULL;
    game->map->map = NULL;
    game->map->width = 0;
    game->map->height = 0;
    // get_map_dims(game->map);// placeholder for the new func
}

void    init_pregame_parse(t_game_data *game)
{
    init_map(game);
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
