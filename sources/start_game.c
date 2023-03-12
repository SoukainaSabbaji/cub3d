/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:52:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/12 11:00:25 by ssabbaji         ###   ########.fr       */
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
		draw_wall_text(game);
		game->x++;
	}
}

uint32_t	my_htons(int32_t nlong)
{
	uint32_t	n;

	n = (nlong >> 24) & 0xff;
	n |= (nlong >> 8) & 0xff00;
	n |= (nlong << 8) & 0xff0000;
	n |= (nlong << 24) & 0xff000000;
	return (n);
}

unsigned int	my_mlx_get_colour(mlx_texture_t *img, unsigned int x,
		unsigned int y)
{
	uint32_t	colour;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return (0);
	colour = ((uint32_t *)(img->pixels))[x + y * img->width];
	return (my_htons(colour));
}
