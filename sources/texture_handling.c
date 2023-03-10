/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:36:41 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/06 11:36:41 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    get_textures(t_game_data *game)
{
        game->n_tex = mlx_load_png("./textures/ac007c51eea4b4bc24500d579b7a8428.png");
        if (game->n_tex == NULL)
            ft_error();
        game->s_tex = mlx_load_png("./textures/images.png");
        if (game->s_tex == NULL)
            ft_error();
        game->w_tex = mlx_load_png("./textures/maxresdefault.png");
        if (game->w_tex == NULL)
            ft_error();
        game->e_tex = mlx_load_png("./textures/311.png");
        if (game->e_tex == NULL)
            ft_error();
}

void    calculate_tex_infos(t_game_data *game, t_text *text, mlx_texture_t *tex)
{
    double    wall_x = 0;

    game->tex_height = 100;
    text->height = 100;
    text->width = 100;
    text->step = 0;
    (void)tex;
    wall_x = find_wall_intersect(game);
    text->tex_x = (int)(text->wall_x * (double) text->width);
    if (game->side == 0 && game->raycast.ray_dir.x < 0)
        text->tex_x = text->width - text->tex_x - 1;
    if (game->side == 1 && game->raycast.ray_dir.y > 0)
        text->tex_x = text->width - text->tex_x - 1;
    text->step = 1.0 * text->height / game->line_height;
    text->tex_pos = (game->draw_start - game->screen_height / 2 + game->line_height / 2) \
        * text->step;
}

void    draw_column(t_game_data *game, mlx_texture_t *wall,  int x)
{
    int    y_coord;

    y_coord = game->draw_start;
    while (y_coord <= game->draw_end)
    {
        game->text->tex_y = (int) game->text->tex_pos;
        if (game->text->tex_y >= (int) 100)
            game->text->tex_y = wall->height - 1;
        game->text->tex_pos += game->text->step;
        mlx_put_pixel(game->img, x, y_coord, \
            my_mlx_get_colour(wall, game->text->tex_x, game->text->tex_y));
        y_coord++;
    }
}

// void    draw_column(t_game_data *game, mlx_texture_t *wall,  int x)
// {
//     int    y_coord;

//     y_coord = game->draw_start;
//     while (y_coord <= game->draw_end)
//     {
//         game->text->tex_y = (int) game->text->tex_pos;
//         if (game->text->tex_y >= (int) wall->height)
//             game->text->tex_y = wall->height - 1;
//         game->text->tex_pos += game->text->step;
//         mlx_put_pixel(game->img, x, y_coord, \
//             my_mlx_get_colour(wall, game->text->tex_x, game->text->tex_y));
//         y_coord++;
//     }
// }


void   draw_wall_text(t_game_data *game)
{
    if (game->side == 0 && game->raycast.step.x == -1)
    {
        calculate_tex_infos(game, game->text, game->n_tex);
        draw_column(game,  game->n_tex, game->x);
    }
    if (game->side == 0 && game->raycast.step.x == 1)
    {
        calculate_tex_infos(game, game->text, game->s_tex);
        draw_column(game, game->s_tex, game->x);

    }
    if (game->side == 1 && game->raycast.step.y == -1)
    {
        calculate_tex_infos(game, game->text, game->w_tex);
        draw_column(game, game->w_tex, game->x);

    }
    if (game->side == 1 && game->raycast.step.y == 1)
    {
        calculate_tex_infos(game, game->text, game->e_tex);
        draw_column(game, game->e_tex, game->x);

    }
}



double  find_wall_intersect(t_game_data *game)
{
    t_fcoord   intersect;
    t_fcoord   scaled;
    normalize_vector(game->raycast.ray_dir);
    scaled = scale_vector(game->raycast.ray_dir, game->raycast.euclid_dist);
    if (game->side == 0)
        intersect.x = game->player.world_pos.y + scaled.y;
    else
        intersect.x = game->player.world_pos.x + scaled.x;
   intersect.x -= floor(intersect.x);
   return (intersect.x);
}