/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:28 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/23 18:34:06 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"



void    init_game_dir(t_game_data *game)
{
    //initial direction vector 
    if (game->start_dir == 'N')
    {
        game->player->dir.x = -1;
        game->player->dir.y = 0;
        game->plane.x = 0;
        game->plane.y = 0.66;
    }
    else if (game->start_dir == 'S')
    {
        game->player->dir.x = 1;
        game->player->dir.y = 0;
        game->plane.x = 0;
        game->plane.y = -0.66;
    }
    else if (game->start_dir == 'E')
    {
        game->player->dir.x = 0;
        game->player->dir.y = 1;
        game->plane.x = 0.66;
        game->plane.y = 0;
    }
    else if (game->start_dir == 'W')
    {
        game->player->dir.x = 0;
        game->player->dir.y = -1;
        game->plane.x = -0.66;
        game->plane.y = 0;
    }
    // game->ray->ray_dir.x = game->player->dir.x;
    // game->ray->ray_dir.y = game->player->dir.y;
    // game->ray->ray_origin.x = game->player->world_pos.x;
    // game->ray->ray_origin.y = game->player->world_pos.y;
}


void    calculate_step(t_game_data *game)
{
    //calculate step and initial sideDist
    if (game->ray_dir.x < 0)
    {
        game->step.x = -1;
        game->side_dist.x = (game->pos.x - game->map_pos.x) * game->delta_dist.x;
    }
    else
    {
        game->step.x = 1;
        game->side_dist.x = (game->map_pos.x + 1.0 - game->pos.x) * game->delta_dist.x;
    }
    if (game->ray_dir.y < 0)
    {
        game->step.y = -1;
        game->side_dist.y = (game->pos.y - game->map_pos.y) * game->delta_dist.y;
    }
    else
    {
        game->step.y = 1;
        game->side_dist.y = (game->map_pos.y + 1.0 - game->pos.y) * game->delta_dist.y;
    }
    
}

void    drawing_calc(t_game_data *game)
{
    // calculate ray position and direction
    //camerax is different from planex
    //planex and y are the 2d raycaster version of camera plane
    //camera plane is the 3d version of planex and y , we normalize 
    //it by dividing it by the screen width so the camera plane
    //is always the same size and always centered on the player 
    
    
    game->camera_plane.x = 2 * game->x / (double)game->screen_width - 1; //x-coordinate in camera space
    game->ray_dir.x = game->ray->ray_dir.x + game->plane.x * game->camera_plane.x;
    game->ray_dir.y = game->ray->ray_dir.y + game->plane.y * game->camera_plane.x;  
    //which box of the map we're in
    game->map_pos.x = (int)game->player->world_pos.x;
    game->map_pos.y = (int)game->player->world_pos.y;
    game->hit = 0;
    //initialize deltaDist vars aaaand done with drawing calc
    game->delta_dist.x = sqrt(1 + (game->ray_dir.y * game->ray_dir.y) / (game->ray_dir.x * game->ray_dir.x));
    //this calculation is to avoid division by 0 (we're not in c++ hehe) and is the same as doing the following
    // game->delta_dist->x = sqrt(1 + pow(game->ray_dir->y, 2) / pow(game->ray_dir->x, 2)) 
    // / pow(game->ray_dir->x, 2);
    // game->delta_dist->x = sqrt(1 + pow(game->ray_dir->y, 2) / pow(game->ray_dir->x, 2))    
    // / pow(game->ray_dir->x, 2);
    game->delta_dist.y = sqrt(1 + (game->ray_dir.x * game->ray_dir.x) / (game->ray_dir.y * game->ray_dir.y));
    // if (game->delta_dist->x == 0) the rest to implement in a separate function
    
}



