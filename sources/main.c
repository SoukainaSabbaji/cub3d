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


int	main(int argc, char **argv)
{
    t_game_data *game;

    game = malloc(sizeof(t_game_data));
    ft_check_input(argc, argv);
    game->map = ft_getmap(argv[1]);
    //init map function to initialize mlx;
    // g_mlx = mlx_init(map->width * WALL_SIZE, map->height * WALL_SIZE, "cub3D", true);
    if (!g_mlx)
        ft_error();
    //draw_map(g_mlx, game->map, (t_coord){map->width * WALL_SIZE, map->height * WALL_SIZE});
    mlx_image_to_window(g_mlx, g_img, 0, 0);
    mlx_loop(g_mlx);
    mlx_loop_hook(g_mlx, &ready_start, game);
    mlx_terminate(g_mlx);
    return (EXIT_SUCCESS);
}
