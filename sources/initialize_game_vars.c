/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:55:31 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/11 21:35:08 by makacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void	find_player_pos(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player->world_pos = (t_fcoord){.x = j + .5, .y = i + .5};
				player->map_pos = (t_coord){.x = j, .y = i};
				init_game_dir(player, map->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_text(t_text *text)
{
	text->width = 64;
	text->height = 64;
	text->tex_x = 0;
	text->tex_y = 0;
	text->step = 0;
	text->wall_x = 0;
}

void	init_game_vars(t_game_data *game)
{
	game->text = malloc(sizeof(t_text));
	init_text(game->text);
	get_textures(game);
	if (!game->text)
		ft_error();
	game->move_speed = 0.05;
	game->rot_angle = 0.03;
	find_player_pos(game->map, &game->player);
}

void	print_map_arr(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

void	init_pregame_parse(t_game_data *game, char **argv)
{
	game->map = ft_getmap(argv[1]);
	game->map->height = ft_getnbrof_lines(argv[1]);
	game->map->width = ft_getnbrof_cols(game->map->map);
	game->screen_height = 720;
	game->screen_width = 1080;
	print_map_arr(game->map->map);
}
