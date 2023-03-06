/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/06 14:45:15 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    start_drawing(t_game_data *game)
{
    game->x = 0;
    while (game->x < game->screen_width)
    {
        drawing_calc(game);
        start_dda(&game->raycast, game->map, game->player.map_pos);
        game->perp_wall_dis = calculate_perp(game->raycast);
        calculate_line_height(game);
        draw_line(game, color);
        game->x++;
    }
}

void   ready_start(void *ptr)
{
    t_game_data *game;

    game = (t_game_data *)ptr;
    init_game_vars(game);
    start_drawing(game);
}
xpm 