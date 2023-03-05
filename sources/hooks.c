/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:53:01 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/04 16:11:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    move_forback(t_game_data *game)
{
    normalize_vector(game->player->dir);
    if (mlx_is_key_down(game->mlx, MLX_KEY_W) )
    {
        printf("move forward\n");
        if (game->map->map[(int)(game->pos.x + game->player->dir.x * game->move_speed)][(int)(game->pos.y)] == '0')
            game->pos.x += game->player->dir.x * game->move_speed;
        if (game->map->map[(int)(game->pos.x)][(int)(game->pos.y + game->player->dir.y * game->move_speed)] == '0')
            game->pos.y += game->player->dir.y * game->move_speed;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S) )
    {
        printf("move backward\n");
        if (game->map->map[(int)(game->pos.x - game->player->dir.x * game->move_speed)][(int)(game->pos.y)] == '0')
            game->pos.x -= game->player->dir.x * game->move_speed;
        if (game->map->map[(int)(game->pos.x)][(int)(game->pos.y - game->player->dir.y * game->move_speed)] == '0')
            game->pos.y -= game->player->dir.y * game->move_speed;
    }
}

void    move_straf(t_game_data *game)
{
    double dx;
    double dy;

    dx = 0;
    dy = 0;
    if (mlx_is_key_down(game->mlx, MLX_KEY_A) )
    {
        // printf("straf left\n");
        // dx = -game->player->dir.y;
        // dy = game->player->dir.x;
        // dx /= vector_size((t_fcoord){dx, dy});
        // dy /= vector_size((t_fcoord){dx, dy});
        // game->pos.x -= dx * STRAFE_SPEED;
        // game->pos.y -= dy * STRAFE_SPEED;
	    // if (game->map->map[(int)(game->pos.x)][(int)(\
	    // 	game->pos.y + game->player->dir.y - game->plane.y)] == '0')
	    // {
	    // 	game->pos.y -= game->plane.y * game->move_speed;
	    // 	game->pos.x -= game->plane.x * game->move_speed;
	    // }
        if (game->map->map[(int)(game->pos.x - game->plane.x * game->move_speed)][(int)(game->pos.y)] == '0')
            game->pos.x -= game->plane.x * game->move_speed;
        if (game->map->map[(int)(game->pos.x)][(int)(game->pos.y - game->plane.y * game->move_speed)] == '0')
            game->pos.y -= game->plane.y * game->move_speed;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D) )
    {
        // printf("straf right\n");
        // dx = game->player->dir.y;
        // dy = -game->player->dir.x;
        // dx /= vector_size((t_fcoord){dx, dy});;
        // dy /= vector_size((t_fcoord){dx, dy});
        // game->pos.x += dx * STRAFE_SPEED;
        // game->pos.y += dy * STRAFE_SPEED;
	    // if (game->map->map[(int)(game->pos.x)][(int)(\
	    // 	game->pos.y + game->player->dir.y + game->plane.y)] == '0')
	    // {
	    // 	game->pos.y += game->plane.y * game->move_speed;
	    // 	game->pos.x += game->plane.x * game->move_speed;
	    // }
        if (game->map->map[(int)(game->pos.x + game->plane.x * game->move_speed)][(int)(game->pos.y)] == '0')
            game->pos.x += game->plane.x * game->move_speed;
        if (game->map->map[(int)(game->pos.x)][(int)(game->pos.y + game->plane.y * game->move_speed)] == '0')
            game->pos.y += game->plane.y * game->move_speed;
    }

}

void    rotate_fov(t_game_data *game)
{
    t_fcoord old_dir;
    t_fcoord old_plane;
    old_dir = game->player->dir;
    old_plane = game->plane;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
    {
        printf("left\n");
        game->player->dir.x = game->player->dir.x * cos(game->rot_angle) - game->player->dir.y * sin(game->rot_angle);
        game->player->dir.y = old_dir.x * sin(game->rot_angle) + game->player->dir.y * cos(game->rot_angle);
        game->plane.x = game->plane.x * cos(game->rot_angle) - game->plane.y * sin(game->rot_angle);
        game->plane.y = old_plane.x * sin(game->rot_angle) + game->plane.y * cos(game->rot_angle);
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
    {
        printf("right\n");
        game->player->dir.x = game->player->dir.x * cos(-game->rot_angle) - game->player->dir.y * sin(-game->rot_angle);
        game->player->dir.y = old_dir.x * sin(-game->rot_angle) + game->player->dir.y * cos(-game->rot_angle);
        game->plane.x = game->plane.x * cos(-game->rot_angle) - game->plane.y * sin(-game->rot_angle);
        game->plane.y = old_plane.x * sin(-game->rot_angle) + game->plane.y * cos(-game->rot_angle);
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
