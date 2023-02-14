/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:06 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/14 17:49:17 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"


void    draw_circle(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
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

t_coord *draw_square(t_coord *points,mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
{
    int i = 0;
    int j = 0;
    
    while (i < size)
    {
        while (j < size)
        {
            int nx = pos.x + i;
            int ny = pos.y + j;
            if (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y)
            {
                mlx_put_pixel(img, nx, ny, color);
                if ((unsigned int)color == PLAYER_COLOR)
                {
                    t_iter iter;

                    iter.i = 0;
                    printf("index and value of coords in the points array[%d][%d, %d]\n", iter.i, nx, ny);
                    points[iter.i].x = nx;
                    points[iter.i].y = ny;
                    iter.i++;
                    
                }
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (points);
}

void draw_line(t_coord p1, t_coord p2, int color)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = 0;
    float x = p1.x + 0.5;
    float y = p1.y + 0.5;
    int i = 0;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    while (i <= steps)
    {
        mlx_put_pixel(g_img, x, y, color);
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