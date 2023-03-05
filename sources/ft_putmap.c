/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:23:28 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:23:46 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	ft_putmap(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	char			*line;
	mlx_image_t	*wall_img;
	mlx_image_t	*space_img;

	x = 0;
	y = 0;
	wall_img = mlx_new_image(mlx, 32, 32);
	space_img = mlx_new_image(mlx, 32, 32);
	ft_memset(wall_img->pixels, 200, wall_img->width * wall_img->height * BPP);
	ft_memset(space_img->pixels, 255, space_img->width * space_img->height * BPP);
	while (*map != '\0')
	{
		line = *map;
		x = 0;
		while (*line != '\0' && *line != '\n')
		{
			if (*line == '1')
				mlx_image_to_window(mlx, wall_img, x, y);
			else if (*line == '0' || *line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
				mlx_image_to_window(mlx, space_img, x, y);
			line++;
			x = x + 32;
		}
		y = y + 32;
		map++;
	}
}