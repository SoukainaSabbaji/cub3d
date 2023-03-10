/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:02:38 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/02 16:02:38 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

int color = 0x00FF0000;

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
    ft_memset(game, 0, sizeof(t_game_data));
    ft_check_input(argc, argv);
    init_pregame_parse(game, argv);
    game->mlx = mlx_init(game->screen_width,game->screen_height, "cub3D", true);
    game->img = mlx_new_image(game->mlx, game->screen_width, game->screen_height);
    if (!game->mlx)
        exit(0);
    draw_floor_ceiling(game);
    init_game_vars(game);
    start_drawing(game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    get_textures(game);
    mlx_loop_hook(game->mlx, &handle_input, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}