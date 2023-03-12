/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/12 10:52:20 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/12 10:52:20 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	get_textures(t_game_data *game)
{
	game->n_tex = mlx_load_png(game->map->n_texture);
	if (game->n_tex == NULL)
		ft_error();
	game->s_tex = mlx_load_png(game->map->s_texture);
	if (game->s_tex == NULL)
		ft_error();
	game->w_tex = mlx_load_png(game->map->w_texture);
	if (game->w_tex == NULL)
		ft_error();
	game->e_tex = mlx_load_png(game->map->e_texture);
	if (game->e_tex == NULL)
		ft_error();
}

t_text	*get_tex_infos(t_game_data *game, mlx_texture_t *tex)
{
	t_text	*text;

	text = game->text;
	text->height = tex->height;
	text->width = tex->width;
	text->wall_x = find_wall_intersect(game);
	text->tex_x = (int)(text->wall_x * (double)text->width);
	if (game->raycast.side == 0 && game->raycast.ray_dir.x < 0)
		text->tex_x = text->width - text->tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.ray_dir.y > 0)
		text->tex_x = text->width - text->tex_x - 1;
	text->step = 1.0 * text->height / game->line_height;
	game->text->tex_pos = (game->draw_start - game->screen_height / 2
			+ game->line_height / 2) * game->text->step;
	return (text);
}

void	draw_wall_text(t_game_data *game)
{
	if (game->raycast.side == 0 && game->raycast.step.x == -1)
	{
		game->text = get_tex_infos(game, game->e_tex);
		draw_column(game, game->e_tex, game->x);
	}
	if (game->raycast.side == 0 && game->raycast.step.x == 1)
	{
		game->text = get_tex_infos(game, game->w_tex);
		draw_column(game, game->w_tex, game->x);
	}
	if (game->raycast.side == 1 && game->raycast.step.y == -1)
	{
		game->text = get_tex_infos(game, game->s_tex);
		draw_column(game, game->s_tex, game->x);
	}
	if (game->raycast.side == 1 && game->raycast.step.y == 1)
	{
		game->text = get_tex_infos(game, game->n_tex);
		draw_column(game, game->n_tex, game->x);
	}
}

void	draw_column(t_game_data *game, mlx_texture_t *wall, int x)
{
	int	y_coord;

	y_coord = game->draw_start;
	while (y_coord <= game->draw_end)
	{
		game->text->tex_y = (int)game->text->tex_pos;
		if (game->text->tex_y >= (int)wall->height)
			game->text->tex_y = game->text->height - 1;
		game->text->tex_pos += game->text->step;
		mlx_put_pixel(game->img, x, y_coord, my_mlx_get_colour(wall,
				game->text->tex_x, game->text->tex_y));
		y_coord++;
	}
}

double	find_wall_intersect(t_game_data *game)
{
	t_fcoord	intersect;
	t_fcoord	scaled;
	t_fcoord	normdir;
	double		text_idx;

	normdir = normalize_vector(game->raycast.ray_dir);
	scaled = scale_vector(normdir, game->raycast.euclid_dist);
	intersect = add_vector(game->player.world_pos, scaled);
	if (game->raycast.side == 0)
		text_idx = intersect.y;
	else
		text_idx = intersect.x;
	text_idx = text_idx - (int)text_idx;
	return (text_idx);
}
