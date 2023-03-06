/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minimapkeyhook.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:25:47 by makacem           #+#    #+#             */
/*   Updated: 2023/03/06 11:21:58 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void my_minimapkeyhook(mlx_key_data_t keydata, void* param)
{
	t_player_map *player_map;
	static double angle;

	player_map = param;

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && ft_check_wall(player_map, -1, 'y') == 0)
	{
		player_map->player_img->instances[0].x -= sin(-angle * M_PI / 180) * 4;
		player_map->player_img->instances[0].y -= cos(-angle * M_PI / 180) * 4;
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);

	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && ft_check_wall(player_map, 1, 'y') == 0)
	{
		player_map->player_img->instances[0].x += sin(-angle * M_PI / 180) * 4;
		player_map->player_img->instances[0].y += cos(-angle * M_PI / 180) * 4;
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && ft_check_wall(player_map, -1, 'x') == 0)
	{
		player_map->player_img->instances[0].x += sin(-angle * M_PI / 180) * 4;
		player_map->player_img->instances[0].y -= cos(-angle * M_PI / 180) * 4;
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && ft_check_wall(player_map, 1, 'x') == 0)
	{
		player_map->ray_img->instances[0].x += 4;
		player_map->player_img->instances[0].x += 4;
	}

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT && ft_check_wall(player_map, -1, 'y') == 0)
	{
		player_map->player_img->instances[0].x -= sin(-angle * M_PI / 180) * 4;
		player_map->player_img->instances[0].y -= cos(-angle * M_PI / 180) * 4;
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT && ft_check_wall(player_map, 1, 'y') == 0)
	{
		player_map->player_img->instances[0].x += sin(-angle * M_PI / 180) * 4;
		player_map->player_img->instances[0].y += cos(-angle * M_PI / 180) * 4;
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT && ft_check_wall(player_map, -1, 'x') == 0)
	{
		player_map->ray_img->instances[0].x -= 4;
		player_map->player_img->instances[0].x -= 4;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT && ft_check_wall(player_map, 1, 'x') == 0)
	{
		player_map->ray_img->instances[0].x += 4;
		player_map->player_img->instances[0].x += 4;
	}

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		angle += 8;
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		angle -= 8;
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		angle += 8;
		if (angle >= 360)
			angle = 0;
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		angle -= 8;
		if (angle <= 0)
			angle = 360;
		player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
		player_map->ray_img = ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, angle);
	}

}