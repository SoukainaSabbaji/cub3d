/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:14:30 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/10 16:47:35 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

double calculate_perp(t_raycast raycast)
{
    double euclidian_dist;

    if (raycast.side == 0)
    {
        euclidian_dist = raycast.side_dist.x - raycast.delta_dist.x;
        return (fabs(euclidian_dist / raycast.delta_dist.x / raycast.ray_dir.x));
    }
    else
    {
        euclidian_dist = raycast.side_dist.y - raycast.delta_dist.y;
        return (fabs(euclidian_dist / raycast.delta_dist.y / raycast.ray_dir.y));
    }
    raycast.euclid_dist = euclidian_dist;
}

void start_dda(t_raycast *raycast, t_map *map, t_coord start_pos)
{
    while (!raycast->hit)
    {
        if (raycast->side_dist.x < raycast->side_dist.y)
        {
            raycast->side_dist.x += raycast->delta_dist.x;
            start_pos.x += raycast->step.x;
            raycast->side = 0;
        }
        else
        {
            raycast->side_dist.y += raycast->delta_dist.y;
            start_pos.y += raycast->step.y;
            raycast->side = 1;
        }
        if (map->map[start_pos.y][start_pos.x] == WALL)
            raycast->hit = 1;
    }
}

void calculate_line_height(t_game_data *game)
{
    // calculate height of line to draw on screen
    //  game->line_height = (int)(game->map->height / game->perp_wall_dis);
    game->line_height = (int)(game->screen_height / game->perp_wall_dis);
    // calculate lowest and highest pixel to fill in current stripe
    game->draw_start = -game->line_height / 2 + game->screen_height / 2;
    
    if (game->draw_start < 0)
        game->draw_start = 0;
    game->draw_end = game->line_height / 2 + game->screen_height / 2;
    if (game->draw_end >= game->screen_height)
        game->draw_end = game->screen_height - 1;
    if (game->raycast.side == 0)
        color = MMAP_WALL_COLOR;
    else 
        color = MMAP_EMPTY_COLOR;
}