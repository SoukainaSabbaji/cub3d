/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putgrid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:20:53 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:21:08 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	ft_putgrid(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	int 		i;
	int			j;
	mlx_image_t	*grid_img;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	map = NULL;
	grid_img = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, grid_img, x, y);
	while (x < mlx->width)
	{
		y = 0;
		while (y < mlx->height)
		{
			mlx_put_pixel(grid_img, x, y, 0x0000FF);
			y++;
		}
		x = x + 32;
	}
	x = 0;
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			mlx_put_pixel(grid_img, x, y, 0x0000FF);
			x++;
		}
		y = y + 32;
	}
}