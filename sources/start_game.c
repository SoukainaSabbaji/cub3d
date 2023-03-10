/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/10 18:47:00 by ssabbaji         ###   ########.fr       */
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
        // draw_wall_text(game);
        game->x++;
    }
}

unsigned int	my_mlx_get_colour(mlx_texture_t *img, unsigned int x, unsigned int y)
{
	unsigned int	*colour;

	colour = (unsigned int *)(img->pixels + ((x + y * img->width) * sizeof(unsigned int)));
	return (*colour);
}