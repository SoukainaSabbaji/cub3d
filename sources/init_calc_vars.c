/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:47:28 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/06 11:37:15 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    init_game_dir(t_player *player, char start_dir)
{
    if (start_dir == 'N')
    {
        player->dir = (t_fcoord){ .x = -1, .y = 0 };
        player->camera_plane = (t_fcoord){ .x = 0, .y = 0.66 };
    }
    if (start_dir == 'S')
    {
        player->dir = (t_fcoord){ .x = 1, .y = 0 };
        player->camera_plane = (t_fcoord){ .x = 0, .y = -0.66 };
    }
    if (start_dir == 'E')
    {
        player->dir = (t_fcoord){ .x = 0, .y = 1 };
        player->camera_plane = (t_fcoord){ .x = 0.66, .y = 0 };
    }
    if (start_dir == 'W')
    {
        player->dir = (t_fcoord){ .x = 0, .y = -1 };
        player->camera_plane = (t_fcoord){ .x = -0.66, .y = 0 };
    }
}

void    init_raycast(t_raycast *raycast, t_player *player, t_fcoord ray_dir)
{
    //calculate step and initial sideDist
    raycast->hit = 0;
    raycast->ray_dir = ray_dir;
    raycast->step.x = fabs(ray_dir.x) / ray_dir.x;
    raycast->step.y = fabs(ray_dir.y) / ray_dir.y;
    raycast->delta_dist.x = (ray_dir.x != 0) ? sqrt(1 + pow(ray_dir.y, 2) / pow(ray_dir.x, 2)) : INT32_MAX;
    raycast->delta_dist.y = (ray_dir.y != 0) ? sqrt(1 + pow(ray_dir.x, 2) / pow(ray_dir.y, 2)) :  INT32_MAX;
    if (ray_dir.x < 0)
        raycast->side_dist.x = player->world_pos.x - player->map_pos.x;
    else
        raycast->side_dist.x = player->map_pos.x + 1.0 - player->world_pos.x;
    raycast->side_dist.x *=  raycast->delta_dist.x;
    if (ray_dir.y < 0)
        raycast->side_dist.y = player->world_pos.y - player->map_pos.y;
    else
        raycast->side_dist.y = player->map_pos.y + 1.0 - player->world_pos.y;
    raycast->side_dist.y *= raycast->delta_dist.y;
}

void    drawing_calc(t_game_data *game)
{
    float       plane_factor;
    t_fcoord    ray_dir;

    plane_factor = 2 * game->x / (double)game->screen_width - 1;
    ray_dir.x = game->player.dir.x + game->player.camera_plane.x * plane_factor;
    ray_dir.y = game->player.dir.y + game->player.camera_plane.y * plane_factor;
    init_raycast(&game->raycast, &game->player, ray_dir);
}