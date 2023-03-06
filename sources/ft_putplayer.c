/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putplayer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:16:13 by makacem           #+#    #+#             */
/*   Updated: 2023/03/06 11:22:21 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

mlx_image_t	*ft_putplayer(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	char			*line;
	mlx_image_t *player_img;

	x = 0;
	y = 0;
	player_img = mlx_new_image(mlx, 1, 1);
	ft_memset(player_img->pixels, 150, player_img->width * player_img->height * BPP);
	ft_putcolor(player_img);
	mlx_put_pixel(player_img, 150, 150, 0xFF0000FF);
	while (*map != '\0')
	{
		line = *map;
		x = 0;
		while (*line != '\0' && *line != '\n')
		{
			if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			{
				mlx_image_to_window(mlx, player_img, x + 16, y + 16);
			}
			line++;
			x = x + 32;
		}
		y = y + 32;
		map++;
	}
	return (player_img);
}
