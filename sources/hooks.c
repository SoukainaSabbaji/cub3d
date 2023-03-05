/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:53:01 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/05 17:56:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"


t_fcoord movement_distance(t_game_data *game, t_fcoord mov, double max_distance)
{
    t_raycast   wall_tester;

    init_raycast(&wall_tester, &game->player, mov);
    start_dda(&wall_tester, game->map, game->player.map_pos);
    if (wall_tester.side == 0)
    {
        if (fabs(wall_tester.side_dist.x - wall_tester.delta_dist.x) < max_distance)
            return scale_vector(mov, 0);
        return scale_vector(mov, max_distance);
    }
    else
    {
        if (fabs(wall_tester.side_dist.y - wall_tester.delta_dist.y) < max_distance)
            return scale_vector(mov, 0);
        return scale_vector(mov, max_distance);
    }   
}

void    move_forback(t_game_data *game)
{
    t_fcoord new_pos;
    t_fcoord orientation;
    t_fcoord mov;

    orientation = normalize_vector(game->player.dir);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        if (mlx_is_key_down(game->mlx, MLX_KEY_W))
            mov = movement_distance(game, orientation, game->move_speed);
        else
            mov = movement_distance(game, scale_vector(orientation, -1), game->move_speed);
        new_pos = add_vector(game->player.world_pos, mov);
        game->player.world_pos = new_pos;
        game->player.map_pos =  (t_coord){ .x = (int)new_pos.x, .y = (int)new_pos.y};
    }
}

void    move_straf(t_game_data *game)
{
    t_fcoord new_pos;
    t_fcoord side_vector;
    t_fcoord mov;

    side_vector = game->player.camera_plane;
    if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        if (mlx_is_key_down(game->mlx, MLX_KEY_D))
            mov = movement_distance(game, side_vector, game->move_speed);
        else
            mov = movement_distance(game, scale_vector(side_vector, -1), game->move_speed);
        new_pos = add_vector(game->player.world_pos, mov);
        game->player.world_pos = new_pos;
        game->player.map_pos =  (t_coord){ .x = (int)new_pos.x, .y = (int)new_pos.y};
    }
}

t_fcoord  rotate_angle(t_fcoord vector, float angle)
{
    t_fcoord new_vector;
    new_vector.x = vector.x * cos(angle) - vector.y * sin(angle);
    new_vector.y = vector.x * sin(angle) + vector.y * cos(angle);
    return (new_vector);
}

void    rotate_fov(t_game_data *game)
{
    t_fcoord old_dir;
    t_fcoord old_plane;
    old_dir = game->player.dir;
    old_plane = game->player.camera_plane;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        game->player.dir = rotate_angle(game->player.dir, game->rot_angle);
        game->player.camera_plane = rotate_angle(game->player.camera_plane, game->rot_angle);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        game->player.dir = rotate_angle(game->player.dir, -game->rot_angle);
        game->player.camera_plane = rotate_angle(game->player.camera_plane, -game->rot_angle);
    }
}

void handle_input(void *param)
{
    t_game_data *game;

    game = param;
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
    move_forback(game);
    move_straf(game);
    rotate_fov(game);
    mlx_delete_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    draw_floor_ceiling(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    start_drawing(game);
}
