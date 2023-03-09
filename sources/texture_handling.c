/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:36:41 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/06 11:36:41 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

// void    get_textures(t_game_data *game)
// {
//     if (game->side == 0 && game->raycast.step.x == -1)
//     //north
//     if (game->side == 0 && game->raycast.step.x == 1)
//     //south
//     if (game->side == 1 && game->raycast.step.y == -1)
//     //west
//     if (game->side == 1 && game->raycast.step.y == 1)
//     //east
//         game->text->n_tex = mlx_load_png(game->map->n_texture);
//         game->text->s_tex = mlx_load_png(game->map->s_texture);
//         game->text->w_tex = mlx_load_png(game->map->w_texture);
//         game->text->e_tex = mlx_load_png(game->map->e_texture);
// }


// /*
// to find the point of intersection for each ray that hits the wall by doing IntersectionPoint = PlayerPos + rayDir * distance
// then if you have an intersection on the horizontal axis you will calculate the fractional part of the X
// and scale it by the size of the texture
// and the other way around for Y and vertical axis


// */
// void    find_wall_intersect(t_game_data *game)
// {
//     t_fcoord   intersect;
//     if (game->side == 0)
//     {
//         intersect.y = game->player.world_pos.y + game->perp_wall_dis * game->raycast.ray_dir.y;
//         intersect.x = game->player.world_pos.x + (intersect.y - game->player.world_pos.y) / tan(game->player.rot_angle);    
//     }
//     else
//     {
//         intersect.x = game->player.world_pos.x + game->perp_wall_dis * game->raycast.ray_dir.x;
//         intersect.y = game->player.world_pos.y + (intersect.x - game->player.world_pos.x) * tan(game->player.rot_angle);
//     }
//     game->wall->x -= floor(game->wall->x);

// }