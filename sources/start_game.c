/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/11 16:39:31 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	start_drawing(t_game_data *game)
{
	game->x = 0;
	while (game->x < game->screen_width)
	{
		drawing_calc(game);
		start_dda(&game->raycast, game->map, game->player.map_pos);
		game->perp_wall_dis = calculate_perp(&game->raycast);
		calculate_line_height(game);
		//if(game->raycast.side == 0)
		draw_wall_text(game);
		game->x++;
	}
}


// void	start_drawing(t_game_data *game)
// {
// 	game->x = 0;
// 	while (game->x < (game->screen_width ))
// 	{
// 		drawing_calc(game);
// 		start_dda(&game->raycast, game->map, game->player.map_pos);
// 		game->perp_wall_dis = calculate_perp(&game->raycast);
// 		calculate_line_height(game);
// 		//if(game->raycast.side == 0)
// 		draw_wall_text(game);
// 		game->x++;
// 	}
// }

uint32_t my_htons(int32_t nlong)
{
    #if BYTE_ORDER == LITTLE_ENDIAN
        return ((uint32_t)((((uint32_t)(nlong) & 0xff000000) >> 24) |
					(((uint32_t)(nlong) & 0x00ff0000) >> 8) |
					(((uint32_t)(nlong) & 0x0000ff00) << 8) |
					(((uint32_t)(nlong) & 0x000000ff) << 24)));
    #else
        return nshort;
    #endif
}


unsigned int 	my_mlx_get_colour(mlx_texture_t *img, unsigned int x,
		unsigned int y)
{
	uint32_t colour;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return (0);
	colour = ((uint32_t *)(img->pixels))[x + y * img->width];
	return my_htons(colour);
}
