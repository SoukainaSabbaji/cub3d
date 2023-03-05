/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:05:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/02 14:06:08 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int valid_coord(t_coord coord, t_map *map)
{
    if (coord.x < 0 || coord.y < 0 || coord.x >= map->width || coord.y >= map->height)
        return (0);
    return (1);
}

t_coord get_coord(int x, int y)
{
    t_coord coord;

    coord.x = x;
    coord.y = y;
    return (coord);
}
