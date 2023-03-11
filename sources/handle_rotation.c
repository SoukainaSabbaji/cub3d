/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:40:38 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/11 12:36:05 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

t_fcoord	rotate_angle(t_fcoord vector, float angle)
{
	t_fcoord	new_vector;

	new_vector.x = vector.x * cos(angle) - vector.y * sin(angle);
	new_vector.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (new_vector);
}

void	rotate_fov(t_game_data *game)
{
	t_fcoord	old_dir;
	t_fcoord	old_plane;

	old_dir = game->player.dir;
	old_plane = game->player.camera_plane;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.dir = rotate_angle(game->player.dir, game->rot_angle);
		game->player.camera_plane = rotate_angle(game->player.camera_plane,
				game->rot_angle);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.dir = rotate_angle(game->player.dir, -game->rot_angle);
		game->player.camera_plane = rotate_angle(game->player.camera_plane,
				-game->rot_angle);
	}
}
