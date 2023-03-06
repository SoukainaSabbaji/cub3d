/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:04:23 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/06 11:35:21 by ssabbaji         ###   ########.fr       */
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

t_fcoord scale_vector(t_fcoord vector, float scalar)
{
    return (t_fcoord){vector.x * scalar, vector.y * scalar};
}

t_fcoord add_vector(t_fcoord vector1, t_fcoord vector2)
{
    return (t_fcoord){vector1.x + vector2.x, vector1.y + vector2.y};
}
