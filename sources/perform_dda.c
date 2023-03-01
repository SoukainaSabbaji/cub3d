/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:14:30 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/28 15:00:00 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

float vector_size(t_fcoord coord)
{
  return sqrt(pow(coord.x, 2) + pow(coord.y, 2));
}


void    init_dda(t_game_data *game)
{
    // t_fcoord new_plane;
    while (game->hit == 0)
    {
        if (game->side_dist.x < game->side_dist.y)
        {
            game->side_dist.x += game->delta_dist.x;
            game->map_pos.x += game->step.x;
            game->side = 0;
        }
        else
        {
            game->side_dist.y += game->delta_dist.y;
            game->map_pos.y += game->step.y;
            game->side = 1;
        }
        if (game->map->map[game->map_pos.x][game->map_pos.y] == '1')
            game->hit = 1;
    }
    //calculate distance projected on camera direction (oblique distance will give fisheye effect!)
    if (game->side == 0)
        game->perp_wall_dist = game->side_dist.x ;
    else
        game->perp_wall_dist = game->side_dist.y ;  
    // if (game->side == 0)
    // {
    //     new_plane.x =  game->plane.x * game->camera_plane.x * game->side_dist.x;
    //     new_plane.y =  game->plane.y * game->camera_plane.y * game->side_dist.x;
    // } 
    // else 
    // {
    //     new_plane.x =  game->plane.x * game->camera_plane.x * game->side_dist.y;
    //     new_plane.y =  game->plane.y * game->camera_plane.y * game->side_dist.y;
    // }
    // if (game->side == 0)
    //     game->perp_wall_dist = sqrt(pow(game->side_dist.x, 2) - pow(vector_size(new_plane), 2)) ;
    // else
    //     game->perp_wall_dist = sqrt(pow(game->side_dist.y, 2) - pow(vector_size(new_plane), 2)) ;

}

void    calculate_line_height(t_game_data *game)
{
    //calculate height of line to draw on screen
    // game->line_height = (int)(game->map->height / game->perp_wall_dist);
    game->line_height = (int)(game->screen_height / game->perp_wall_dist);
    //calculate lowest and highest pixel to fill in current stripe
    game->draw_start = -game->line_height / 2 + game->screen_height / 2;
    if (game->draw_start < 0)
        game->draw_start = 0;
    game->draw_end = game->line_height / 2 + game->screen_height / 2;
    if (game->draw_end >= game->screen_height)
        game->draw_end = game->screen_height - 1;
}
