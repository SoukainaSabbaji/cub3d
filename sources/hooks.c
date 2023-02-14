/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:53:01 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/14 14:10:51 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void hook(void *param)
{
    mlx_t *mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
}

void hook_2(void *param)
{
    mlx_t *mlx;

    mlx = param;
    //rotate player
    // if (mlx_is_key_down(mlx, MLX_KEY_UP))
    //     rotate_player(0.1);
    // if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
    //     rotate_player(-0.1);
    // if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    //     rotate_player(0.1);
    // if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    //     rotate_player(-0.1);
    if (mlx_is_key_down(mlx, MLX_KEY_W))
        move_player((t_fcoord){0, -0.1});
    if (mlx_is_key_down(mlx, MLX_KEY_S))
        move_player((t_fcoord){0, 0.1});
    if (mlx_is_key_down(mlx, MLX_KEY_A))
        move_player((t_fcoord){-0.1, 0});
    if (mlx_is_key_down(mlx, MLX_KEY_D))
        move_player((t_fcoord){0.1, 0});
}