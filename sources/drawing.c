/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:06 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/28 13:57:22 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minimap.h"

void draw_circle(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
{
    for (int nx = pos.x; nx < size; nx++)
    {
        for (int ny = pos.y; ny < size; ny++)
        {
            int dx = nx - size / 2;
            int dy = ny - size / 2;
            int dist = dx * dx + dy * dy;
            int radius = size / 4;
            if (dist < radius * radius && (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y))
                mlx_put_pixel(img, nx, ny, color);
        }
    }
}

t_coord *draw_square(t_coord *points, mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
{
    t_iter iter = {0, 0, 0};
    while (iter.i < size)
    {
        while (iter.j < size)
        {
            int nx = pos.x + iter.i;
            int ny = pos.y + iter.j;
            if (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y)
            {
                mlx_put_pixel(img, nx, ny, color);
                if ((unsigned int)color == PLAYER_COLOR)
                {
                    t_iter iter;

                    iter.i = 0;
                    points[iter.i].x = nx;
                    points[iter.i].y = ny;
                    iter.i++;
                    
                }
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (points);
}


// a version of draw square that iterates through a t_coord array and draws a pixel at each point

void    draw_square_2(t_coord *points, mlx_image_t *img, int color, int size)
{
    int i = 0;

    while (i < size * size)
    {
        mlx_put_pixel(img, points[i].x, points[i].y, color);
        i++;
    }
}


// void draw_line(t_coord p1, t_coord p2, int color ,mlx_image_t *img)
// {
//     int dx = p2.x - p1.x;
//     int dy = p2.y - p1.y;
//     int steps = 0;
//     float x = p1.x + 0.5;
//     float y = p1.y + 0.5;
//     int i = 0;

//     if (abs(dx) > abs(dy))
//         steps = abs(dx);
//     else
//         steps = abs(dy);
//     float x_inc = dx / (float)steps;
//     float y_inc = dy / (float)steps;
//     while (i <= steps)
//     {
//         // if (x >= 0 && x < dims.x && y >= 0 && y < dims.y)
//         mlx_put_pixel(img, x, y, color);
//         x += x_inc;
//         y += y_inc;
//         i++;
//     }
// }

void draw_line(t_game_data *game, int color)
{

    t_coord p1;
    t_coord p2;

    p1.x = game->x;
    p1.y = game->draw_start;
    p2.x = game->x;
    p2.y = game->draw_end;
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = 0;
    float x = p1.x + 0.5;
    float y = p1.y + 0.5;
    int i = 0;
    // printf("p1.x = %d, p1.y = %d, p2.x = %d, p2.y = %d", p1.x, p1.y, p2.x, p2.y);
    (void)color;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    while (i <= steps)
    {
        mlx_put_pixel(game->img, x, y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

int slope_calc(int param_1, int param_2)
{
    int sx;
    int sy;

    sx = 0;
    sy = 0;
    if (param_1 < param_2)
        return (1);
    else
        return (-1);
}

int error_calc(int dx, int dy)
{
    if (dx > dy)
        return (dx);
    else
        return (-dx);
}

void ft_drawline(t_coord p1, t_coord p2, int color)
{
    t_cord x;
    t_cord y;

    x.d = abs(p2.x - p1.x);
    y.d = abs(p2.y - p1.y);
    x.slope = slope_calc(p1.x, p2.x);
    y.slope = slope_calc(p1.y, p2.y);
    x.error = error_calc(x.d, y.d) / 2;
    while (p1.x != p2.x || p1.y != p2.y)
    {
        mlx_put_pixel(g_img, p1.x, p1.y, color);
        y.error = x.error;
        if (y.error > -x.d)
        {
            x.error -= y.d;
            p1.x += x.slope;
        }
        if (y.error < y.d)
        {
            x.error += x.d;
            p1.y += y.slope;
        }
    }
}

int     conv_rgb(t_rgb color)
{
    return (color.r << 16 | color.g << 8 | color.b);
}

void    draw_rectangles(mlx_image_t *img, t_coord pos, t_coord dims, int color)
{
    t_iter iter = {0, 0, 0};
    while (iter.i < dims.x)
    {
        while (iter.j < dims.y)
        {
            int nx = pos.x + iter.i;
            int ny = pos.y + iter.j;
            if (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y)
            {
                mlx_put_pixel(img, nx, ny, color);
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
}

void    draw_floor_ceiling(t_game_data *game)
{
    t_coord pos;
    t_coord dims;
    int color;

    pos.x = 0;
    pos.y = 0;
    dims.x = game->screen_width;
    dims.y = game->screen_height;
    color = conv_rgb(game->map->floor);
    draw_rectangles(game->img, pos, dims, RAY_COLOR);
    pos.y = 0;
    dims.x = game->screen_width;
    dims.y = game->screen_height / 2;
    color = conv_rgb(game->map->ceiling);
    draw_rectangles(game->img, pos, dims, PLAYER_COLOR);
}