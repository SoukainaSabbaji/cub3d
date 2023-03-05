/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:14:57 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:15:52 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

mlx_image_t	*ft_initrays(mlx_t *mlx, mlx_image_t *player)
{
	int			x;
	int			y;

	mlx_image_t *ray_img;
	int p1_x;
	int	p1_y;
	int p2_x;
	int p2_y;

	x = player->instances[0].x ;
	y = player->instances[0].y ;
	ray_img = mlx_new_image(mlx, mlx->width * 2, mlx->width * 2);

	p1_x = ray_img->width / 2;
	p1_y = ray_img->height / 2;
	p2_x = p1_x - (p1_y * tan(30 * M_PI / 180));
	p2_y = 0;

	return (ray_img);
}
