/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:27:24 by makacem           #+#    #+#             */
/*   Updated: 2023/03/05 11:27:53 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int	ft_check_nextpos(int x, int y, char **map);

int	ft_check_wall(t_player_map *player_map, int i, char x_y)
{
	int next_y;
	int	next_x;

	if (x_y == 'y')
	{
		if (i == 1)
		{
			next_y = player_map->player_img->instances[0].y + 1;
			next_x = player_map->player_img->instances[0].x;
			if (ft_check_nextpos(next_x, next_y, player_map->map) == 0)
				return (0);
		}
		else if (i == -1)
		{
			next_y = player_map->player_img->instances[0].y - 1;
			next_x = player_map->player_img->instances[0].x;
			if (ft_check_nextpos(next_x, next_y, player_map->map) == 0)
				return (0);
		}
	}
	else if (x_y == 'x')
	{
		if (i == 1)
		{
			next_y = player_map->player_img->instances[0].y;
			next_x = player_map->player_img->instances[0].x + 1;
			if (ft_check_nextpos(next_x, next_y, player_map->map) == 0)
				return (0);
		}
		else if (i == -1)
		{
			next_y = player_map->player_img->instances[0].y;
			next_x = player_map->player_img->instances[0].x - 1;
			if (ft_check_nextpos(next_x, next_y, player_map->map) == 0)
				return (0);
		}
	}
	return (1);
}

int	ft_check_nextpos(int x, int y, char **map)
{
	int i;
	int j;

	i = y / 32;
	j = x / 32;
	if (map[i][j] == '1')
		return (1);
	return(0);
}