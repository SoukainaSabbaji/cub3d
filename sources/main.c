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
	char	**map2d;

	ft_check_input(argc, argv);
	map2d = ft_getmap2d(argv[1]);
	ft_check_map2d(map2d);
	g_mlx = mlx_init(1280, 720, "cub3D", true);
	if (!g_mlx)
		ft_error();
    // draw_map(g_mlx, map, (t_coord){map->width * WALL_SIZE, map->height * WALL_SIZE});
    // mlx_image_to_window(g_mlx, g_img, 0, 0);
    // mlx_loop(g_mlx);
    // mlx_terminate(g_mlx);
    return (EXIT_SUCCESS);
}
