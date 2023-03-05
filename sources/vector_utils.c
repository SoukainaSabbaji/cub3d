/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:04:23 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/02 14:06:59 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

float vector_size(t_fcoord coord)
{
    return sqrt(pow(coord.x, 2) + pow(coord.y, 2));
}

t_fcoord normalize_vector(t_fcoord vector)
{
    double  len;

    len = vector_size(vector);
    vector.x /= len;
    vector.y /= len;
    return (vector);
}

