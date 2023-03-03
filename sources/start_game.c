/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/03 15:47:59 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    start_drawing(t_game_data *game)
{
    game->x = 0;
    while (game->x < game->screen_width)
    {
        drawing_calc(game);
        calculate_step(game);
        init_dda(game);
        calculate_line_height(game);
        draw_line(game, color);
        game->x++;
    }
}

void   ready_start(void *ptr)
{
    t_game_data *game;

    game = (t_game_data *)ptr;
    // g_game = game;
    // game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    // mlx_image_to_window(game->mlx, game->img, 0, 0);
    init_player(game);
    init_game_vars(game);
    // mlx_clear_window(game->cube->mlx, game->cube->win);
    // glfw_clear_window(game->cube->win);
    // mlx_loop_hook(game->mlx, &hook_2, game);
    // mlx_loop_hook(game->mlx, &hook, game);
    start_drawing(game);
}
