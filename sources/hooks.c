/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:53:01 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/02 17:19:42 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void hook(void *param)
{
    mlx_t *mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
    {
        printf("Escape key pressed\n"   );
        mlx_close_window(mlx);
    }
}


void hook_2(void *param)
{
    mlx_t *mlx;

    mlx = param;
    t_fcoord old_dir;
    t_fcoord old_plane;
    old_dir = g_game->player->dir;
    old_plane = g_game->plane;
    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        if (g_game->map->map[(int)(g_game->map_pos.x + g_game->player->dir.x * g_game->move_speed)][(int)(g_game->map_pos.y)] == '0')
            g_game->map_pos.x += g_game->player->dir.x * g_game->move_speed;
    } 
    if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
        if (g_game->map->map[(int)(g_game->map_pos.x - g_game->player->dir.x * g_game->move_speed)][(int)(g_game->map_pos.y)] == '0')
            g_game->map_pos.x -= g_game->player->dir.x * g_game->move_speed;
    }
    if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
        g_game->player->dir.x = g_game->player->dir.x * cos(g_game->rot_angle) - g_game->player->dir.y * sin(g_game->rot_angle);
        g_game->player->dir.y = old_dir.x * sin(g_game->rot_angle) + g_game->player->dir.y * cos(g_game->rot_angle);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_D))
    {
        g_game->player->dir.x = g_game->player->dir.x * cos(-g_game->rot_angle) - g_game->player->dir.y * sin(-g_game->rot_angle);
        g_game->player->dir.y = old_dir.x * sin(-g_game->rot_angle) + g_game->player->dir.y * cos(-g_game->rot_angle);
    }

}

void    esc_keyhook(mlx_key_data_t data, void *param)
{
    mlx_t *mlx;

    mlx = param;
    if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
    {
        mlx_close_window(mlx);
    }
        // mlx_close_window(mlx);
}