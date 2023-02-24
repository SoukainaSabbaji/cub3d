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
    init_pregame_parse(game);
    game->mlx = mlx_init(game->screen_width,game->screen_height, "cub3D", true);
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    if (!game->mlx)
        exit(0);
    draw_floor_ceiling(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_loop(game->mlx);
    mlx_loop_hook(game->mlx, &ready_start, game);
    mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}
