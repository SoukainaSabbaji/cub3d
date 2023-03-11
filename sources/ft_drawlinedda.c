/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawlinedda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:33:57 by makacem           #+#    #+#             */
/*   Updated: 2023/03/09 19:14:04 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void ft_drawlinedda(t_coord p1, t_coord p2, int color , mlx_image_t *ray_img)
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
        // if (x >= 0 && x < dims.x && y >= 0 && y < dims.y)
        mlx_put_pixel(ray_img, x, y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}