/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:55:06 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/11 14:58:38 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void draw_square(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
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
                mlx_put_pixel(img, nx, ny, color);
            j++;
        }
        j = 0;
        i++;
    }
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
        mlx_put_pixel(g_img,x, y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}