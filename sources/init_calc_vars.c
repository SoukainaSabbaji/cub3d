/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:28 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/19 15:55:22 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    init_game_vars(t_game_data *game)
{
    //posx and posy start position are the same as the position of the player in the map
    game->pos->x = game->player->world_pos.x;
    game->pos->y = game->player->world_pos.y;
    game->time = 0;
    game->old_time = 0;
    game->move_speed = 0.3;
    game->rot_angle = 0.2;
    init_game_dir(game);
}

void    init_game_dir(t_game_data *game)
{
    //initial direction vector 
    if (game->start_dir == 'N')
    {
        game->player->dir.x = -1;
        game->player->dir.y = 0;
        game->plane->x = 0;
        game->plane->y = 0.66;
    }
    else if (game->start_dir == 'S')
    {
        game->player->dir.x = 1;
        game->player->dir.y = 0;
        game->plane->x = 0;
        game->plane->y = -0.66;
    }
    else if (game->start_dir == 'E')
    {
        game->player->dir.x = 0;
        game->player->dir.y = 1;
        game->plane->x = 0.66;
        game->plane->y = 0;
    }
    else if (game->start_dir == 'W')
    {
        game->player->dir.x = 0;
        game->player->dir.y = -1;
        game->plane->x = -0.66;
        game->plane->y = 0;
    }
    // game->ray->ray_dir.x = game->player->dir.x;
    // game->ray->ray_dir.y = game->player->dir.y;
    // game->ray->ray_origin.x = game->player->world_pos.x;
    // game->ray->ray_origin.y = game->player->world_pos.y;
}


void    drawing_calc(t_game_data *game)
{
    // calculate ray position and direction
    //camerax is different from planex
    //planex and y are the 2d raycaster version of camera plane
    //camera plane is the 3d version of planex and y , we normalize 
    //it by dividing it by the screen width so the camera plane
    //is always the same size and always centered on the player 
    game->camera_plane->x = 2 * game->x / (double)game->screeen_width - 1; //x-coordinate in camera space
    game->ray_dir->x = game->ray->ray_dir.x + game->plane->x * game->camera_plane->x;
    game->ray_dir->y = game->ray->ray_dir.y + game->plane->y * game->camera_plane->x;  
    //which box of the map we're in
    game->map_pos->x = (int)game->player->world_pos.x;
    game->map_pos->y = (int)game->player->world_pos.y;
}


void    init_pregame_parse(t_game_data *game)
{
    
}

void    init_map(t_game_data *game)
{
    game->map->e_texture = NULL;
    game->map->n_texture = NULL;
    game->map->s_texture = NULL;
    game->map->w_texture = NULL;
    get_map_dims(game->map);
}


/* steps to follow */
// 1. init the game variables , like screeb width and height , pointers related to mlx and so on
// 2. init_game_vars
// 3. make a function that starts the game and put it in the mlx_loop_hook
