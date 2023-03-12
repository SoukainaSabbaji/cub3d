/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:06 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/12 11:08:28 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

unsigned int	conv_rgb(t_rgb color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 0xFF);
}

void	draw_rectangles(mlx_image_t *img, t_coord pos, t_coord dims,
		unsigned int color)
{
	t_iter	iter;
	int		nx;
	int		ny;

	iter.i = 0;
	iter.j = 0;
	while (iter.i < dims.x)
	{
		while (iter.j < dims.y)
		{
			nx = pos.x + iter.i;
			ny = pos.y + iter.j;
			if (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y)
				mlx_put_pixel(img, nx, ny, color);
			iter.j++;
		}
		iter.j = 0;
		iter.i++;
	}
}

void	draw_floor_ceiling(t_game_data *game)
{
	t_coord	pos;
	t_coord	dims;

	pos.x = 0;
	pos.y = 0;
	dims.x = game->screen_width;
	dims.y = game->screen_height;
	draw_rectangles(game->img, pos, dims, conv_rgb(game->map->floor));
	pos.x = 0;
	pos.y = 0;
	dims.x = game->screen_width;
	dims.y = game->screen_height / 2;
	draw_rectangles(game->img, pos, dims, conv_rgb(game->map->ceiling));
}
