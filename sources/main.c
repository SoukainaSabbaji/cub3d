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

//count the number of characters in the longest line of the map

int ft_getnbrof_cols(char **map)
{
    int i;
    int j;
    int max;

    i = 0;
    j = 0;
    max = 0;
    while (map[i])
    {
        while (map[i][j])
            j++;
        if (j > max)
            max = j;
        j = 0;
        i++;
    }
    return (max);
}

int	main(int argc, char **argv)
{
    t_game_data *game;

    game = malloc(sizeof(t_game_data));
    ft_check_input(argc, argv);
    game->map = ft_getmap(argv[1]);
    init_pregame_parse(game);
    game->map->height = ft_getnbrof_lines(argv[1]);
    printf("height = %d\n", game->map->height);
    // game->map->width = ft_getnbrof_cols(game->map->map);
    game->mlx = mlx_init(game->screen_width,game->screen_height, "cub3D", true);
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    if (!game->mlx)
        exit(0);
    draw_floor_ceiling(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_loop_hook(game->mlx, &ready_start, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}
