/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:14:30 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/03 12:58:39 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

double  calculate_perp(t_game_data *game)
{
    t_fcoord delta;
    double perp_wall_dis;

    delta.x = game->map_pos.x - game->player->world_pos.x + (1 - game->step.x) / 2;
    delta.y = game->map_pos.y - game->player->world_pos.y + (1 - game->step.y) / 2;
    if (game->side == 0)
    {
        if (game->ray_dir.x == 0)
            perp_wall_dis = INFINITY;
        else
            perp_wall_dis = fabs(delta.x / game->ray_dir.x);
    }
    else
    {
        if (game->ray_dir.y == 0)
            perp_wall_dis = INFINITY;
        else
            perp_wall_dis = fabs(delta.y / game->ray_dir.y);
    }
    return (perp_wall_dis);
}

void init_dda(t_game_data *game)
{
    while (!game->hit && valid_coord(game->map_pos, game->map))
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
        // printf("map_pos.x = %d, map_pos.y = %d\n", game->map_pos.x, game->map_pos.y);
        if (game->map->map[game->map_pos.x][game->map_pos.y] == WALL)
            game->hit = 1;
    }
    game->perp_wall_dis = calculate_perp(game);
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
    if (game->side == 0)
        color = MMAP_WALL_COLOR;
    else 
        color = MMAP_EMPTY_COLOR;
}
