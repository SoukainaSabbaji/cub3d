/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/01 12:24:41 by ssabbaji         ###   ########.fr       */
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
        if (game->side == 0)
            color = MMAP_WALL_COLOR;
        else 
            color = MMAP_EMPTY_COLOR;
        draw_line(game, color);
        game->x++;
    }
}

void   ready_start(void *ptr)
{
    t_game_data *game;

    game = (t_game_data *)ptr;
    init_player(game);
    init_game_vars(game);
    // mlx_clear_window(game->cube->mlx, game->cube->win);
    // glfw_clear_window(game->cube->win);
    start_drawing(game);
}
