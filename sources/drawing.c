/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:06 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/11 12:43:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	get_values(t_game_data *game, t_coord *p1, t_coord *p2, t_coord *d)
{
	p1->x = game->x;
	p1->y = game->draw_start;
	p2->x = game->x;
	p2->y = game->draw_end;
	d->x = p2->x - p1->x;
	d->y = p2->y - p1->y;
}

void	draw_line(t_game_data *game, int color)
{
	t_coord		p1;
	t_coord		p2;
	t_coord		d;
	t_fcoord	f;
	t_fcoord	incr;
	int			steps;
	int			i;

	steps = 0;
	i = 0;
	get_values(game, &p1, &p2, &d);
	f.x = p1.x + 0.5;
	f.y = p1.y + 0.5;
	if (abs(d.x) > abs(d.y))
		steps = abs(d.x);
	else
		steps = abs(d.y);
	incr.x = d.x / (float)steps;
	incr.y = d.y / (float)steps;
	while (i <= steps)
	{
		mlx_put_pixel(game->img, f.x, f.y, color);
		f.x += incr.x;
		f.y += incr.y;
		i++;
	}
}

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
