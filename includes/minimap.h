/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:35 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/12 18:03:45 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mlx.h>

typedef struct s_map
{
    int **map;
    int height;
    int width;
}   t_map;

typedef struct s_cube
{
    void    *mlx;
    void    *win;
    t_map   *map;
    char    *img_data;
    void    *img_ptr;
    int     bpp;
    int     line_size;
    int     endian;
}   t_cube;

#endif