/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:49 by makacem           #+#    #+#             */
/*   Updated: 2023/02/15 13:33:49 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

#define WIDTH 2000
#define HEIGHT 1000


// ********** MAIN ************** //
int32_t main(int argc, char **argv)
{
	t_game_data	*game;
	t_player_map *player_map;

	player_map = malloc(sizeof(t_player_map));
	game = malloc(sizeof(t_game_data));
	ft_check_input(argc, argv);
	game->map = ft_getmap(argv[1]);
	player_map->mlx = mlx_init(ft_getwidth(game->map->map) * 32, ft_getheight(game->map->map) * 32, "minimap2D", true);
	if (!player_map->mlx)
		ft_error();
	ft_putmap(player_map->mlx, game->map->map);
	ft_putgrid(player_map->mlx, game->map->map);
	player_map->player_img = ft_putplayer(player_map->mlx, game->map->map);

	player_map->ray_img = ft_initrays(player_map->mlx, player_map->player_img);
	ft_putray(player_map->mlx, player_map->player_img, player_map->ray_img, 0);
	player_map->map = game->map->map;

	mlx_key_hook(player_map->mlx, &my_minimapkeyhook, player_map);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(player_map->mlx);
	mlx_terminate(player_map->mlx);

    return (EXIT_SUCCESS);
}






