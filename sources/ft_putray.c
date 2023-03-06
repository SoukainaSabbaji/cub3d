/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:12:40 by makacem           #+#    #+#             */
/*   Updated: 2023/03/06 10:38:21 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

mlx_image_t	*ft_putray(mlx_t *mlx, mlx_image_t *player, mlx_image_t *ray_img, double j)
{
	int			x;
	int			y;
	int			x1;
	int			y1;
 
	t_coord p1;
	t_coord p2;

	double	i;

	x = player->instances[0].x ;
	y = player->instances[0].y ;

	mlx_image_to_window(mlx,ray_img, x - (ray_img->width / 2), y - (ray_img->height / 2));

	p1.x = ray_img->width / 2;
	p1.y = ray_img->height / 2;
	

	p2.x = ray_img->width;
	p2.y = ray_img->height / 2;

	x1 = p2.x;
	y1 = p2.y;

	x1 = x1-p1.x;
	y1 = y1-p1.y;
	i = j;
	// while (i < 30 + j)
	// {
		p2.x = x1 * cos(-i * M_PI / 180) - y1 * sin(-i * M_PI / 180);
		p2.y = x1 * sin(-i * M_PI / 180) + y1 * cos(-i * M_PI / 180);
		p2.x = p2.x+p1.x;
		p2.y = p2.y+p1.y;
		printf("ray(%d, %d)  angle = %f   player(%d, %d)\n", p2.x, p2.y, i, p1.x, p1.y);
		ft_drawlinedda(p2, p1, 0xFF0000FF, ray_img);
	// 	i = i + 0.5;
	// }
	return (ray_img);
}
