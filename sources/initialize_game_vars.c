/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:55:31 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/27 14:50:38 by ssabbaji         ###   ########.fr       */
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
    game->ray_dir.x = 0;
    game->ray_dir.y = 0;
    game->delta_dist.x = 0;
    game->delta_dist.y = 0;
    game->side_dist.x = 0;
    game->side_dist.y = 0;
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
                game->player->world_pos = (t_fcoord){.x = j + .5, .y = i + .5};
                game->player->map_pos   = (t_coord){.x = j, .y = i};            
                game->start_dir = map->map[i][j];
                // printf("player pos: %f, %f\n", game->player->world_pos.x, game->player->world_pos.y);
                // printf("player pos: %d %f, %f\n", (game->screen_width / game->map->width), game->player->world_pos.x * (game->screen_width / game->map->width), game->player->world_pos.y * (game->screen_width / game->map->width));
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
    game->player = malloc(sizeof(t_player));
    game->player->world_pos.x = 0;
    game->player->world_pos.y = 0;
    find_player_pos(game);
}

void    init_pregame_parse(t_game_data *game, char **argv)
{
    game->map = ft_getmap(argv[1]);
    game->map->height = ft_getnbrof_lines(argv[1]);
    game->map->width = ft_getnbrof_cols(game->map->map);
    game->screen_height = 480;
    game->screen_width = 640;
    init_player(game);
    // game->image->img_data
    // game->cube->win = mlx_new_window(game->cube->mlx, game->screen_width, game->screen_height, "minimap");
    // game->img->pixels = (int *)mlx_get_data_addr(game->image->img_ptr, &game->image->bpp, &game->image->size_line, &game->image->endian); 
}

/* steps to follow */
// 1. init_pregane_parse
// 2. init_game_vars
// 3. make a function that starts the game and put it in the mlx_loop_hook
