/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:02:38 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/02 16:02:38 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int color = 0x00FF0000;

int ft_getnbrof_cols(char **map)
{
    int i;
    int j;
    int max;

    i = 0;
    j = 0;
    max = 0;
    while (map[i])
    {
        while (map[i][j])
            j++;
        if (j > max)
            max = j;
        j = 0;
        i++;
    }
    return (max);
}

int	main(int argc, char **argv)
{
    t_game_data *game;

    game = malloc(sizeof(t_game_data));
    ft_check_input(argc, argv);
    init_pregame_parse(game, argv);
    game->mlx = mlx_init(game->screen_width,game->screen_height, "cub3D", true);
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    if (!game->mlx)
        exit(0);
    draw_floor_ceiling(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    // mlx_key_hook(game->mlx, &esc_keyhook, game);
    mlx_loop_hook(game->mlx, &handle_input, game);
    mlx_loop_hook(game->mlx, &ready_start, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}



/*
- posX/posY : pos.x = game->player->world_pos.x; pos.y = game->player->world_pos.y;
- dirX/dirY : game->player->dir.x = -1; game->player->dir.y = 0; depending on the start orientation
- planeX/planeY : game->plane.x = 0; game->plane.y = 0.66; depending on the start orientation
- cameraX : game->camera.x = 2 * x / (double)game->screen_width - 1;
- rayDirX : game->ray_dir.x = game->player->dir.x + game->plane.x * game->camera.x;
- rayDirY : game->ray_dir.y = game->player->dir.y + game->plane.y * game->camera.x;
- mapX : game->map.x = (int)game->player->world_pos.x;
- mapY : game->map.y = (int)game->player->world_pos.y;
*/