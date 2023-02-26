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
#define BPP sizeof(int32_t)


typedef struct s_player_map
{
	mlx_t		*mlx;
    mlx_image_t *player_img;
	mlx_image_t *ray_img;
    char **map;
}   t_player_map;

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

mlx_image_t	*ft_putray_north(mlx_t *mlx, mlx_image_t *player, char **map);
mlx_image_t	*ft_putray_west(mlx_t *mlx, mlx_image_t *player, char **map);
mlx_image_t	*ft_putray_south(mlx_t *mlx, mlx_image_t *player, char **map);
mlx_image_t	*ft_putray_east(mlx_t *mlx, mlx_image_t *player, char **map);

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_player_map *player_map;

	player_map = param;

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && ft_check_wall(player_map, -1, 'y') == 0)
	{
		player_map->ray_img->instances[0].y -= 4;
		player_map->player_img->instances[0].y -= 4;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && ft_check_wall(player_map, 1, 'y') == 0)
	{
		player_map->ray_img->instances[0].y += 4;
		player_map->player_img->instances[0].y += 4;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && ft_check_wall(player_map, -1, 'x') == 0)
	{
		player_map->ray_img->instances[0].x -= 4;
		player_map->player_img->instances[0].x -= 4;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && ft_check_wall(player_map, 1, 'x') == 0)
	{
		player_map->ray_img->instances[0].x += 4;
		player_map->player_img->instances[0].x += 4;
	}

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT && ft_check_wall(player_map, -1, 'y') == 0)
	{
		player_map->ray_img->instances[0].y -= 4;
		player_map->player_img->instances[0].y -= 4;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT && ft_check_wall(player_map, 1, 'y') == 0)
	{
		player_map->ray_img->instances[0].y += 4;
		player_map->player_img->instances[0].y += 4;
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
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		if (player_map->ray_img->dir == 'N')
			player_map->ray_img = ft_putray_west(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'W')
			player_map->ray_img = ft_putray_south(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'S')
			player_map->ray_img = ft_putray_east(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'E')
			player_map->ray_img = ft_putray_north(player_map->mlx, player_map->player_img, player_map->map);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(player_map->mlx, player_map->ray_img);
		if (player_map->ray_img->dir == 'N')
			player_map->ray_img = ft_putray_east(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'W')
			player_map->ray_img = ft_putray_north(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'S')
			player_map->ray_img = ft_putray_west(player_map->mlx, player_map->player_img, player_map->map);
		else if (player_map->ray_img->dir == 'E')
			player_map->ray_img = ft_putray_south(player_map->mlx, player_map->player_img, player_map->map);
	}

}

// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

int	ft_getwidth(char **map);
int	ft_getheight(char **map);

void		ft_putmap(mlx_t *mlx, char **map);
void		ft_putgrid(mlx_t *mlx, char **map);
mlx_image_t	*ft_putplayer(mlx_t *mlx, char **map);

mlx_image_t	*ft_putray_south(mlx_t *mlx, mlx_image_t *player, char **map)
{
	int			x;
	int			y;

	int			i;
	int			j;
	int			r;
	mlx_image_t *ray_img;

	map = NULL;
	x = player->instances[0].x ;
	y = player->instances[0].y ;
	ray_img = mlx_new_image(mlx, mlx->width * 2, mlx->height * 2);
	ft_memset(ray_img->pixels, 0, ray_img->width * ray_img->height * BPP);
	mlx_image_to_window(mlx,ray_img, x - (ray_img->width / 2), y - (ray_img->height / 2));
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	r = ray_img->height / 2;
	printf("ray len=%d\n", r);
	printf("start (%d, %d)\n", i, j);
	while ( j < (int)ray_img->height )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j++;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j < (int)ray_img->height )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j++;
		i++;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j < (int)ray_img->height )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j++;
		i--;
	}
	printf("finish (%d, %d)\n", i, j);
	ray_img->dir = 'S';
	return (ray_img);
}

mlx_image_t	*ft_putray_west(mlx_t *mlx, mlx_image_t *player, char **map)
{
	int			x;
	int			y;

	int			i;
	int			j;
	int			r;
	mlx_image_t *ray_img;

	map = NULL;
	x = player->instances[0].x ;
	y = player->instances[0].y ;
	ray_img = mlx_new_image(mlx, mlx->width * 2, mlx->height * 2);
	ft_memset(ray_img->pixels, 0, ray_img->width * ray_img->height * BPP);
	mlx_image_to_window(mlx,ray_img, x - (ray_img->width / 2), y - (ray_img->height / 2));
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	r = ray_img->height / 2;
	printf("ray len=%d\n", r);
	printf("start (%d, %d)\n", i, j);
	while ( i > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		i--;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j--;
		i--;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j < (int)ray_img->height )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j++;
		i--;
	}
	printf("finish (%d, %d)\n", i, j);
	ray_img->dir = 'W';
	return (ray_img);
}

mlx_image_t	*ft_putray_east(mlx_t *mlx, mlx_image_t *player, char **map)
{
	int			x;
	int			y;

	int			i;
	int			j;
	int			r;
	mlx_image_t *ray_img;

	map = NULL;
	x = player->instances[0].x ;
	y = player->instances[0].y ;
	ray_img = mlx_new_image(mlx, mlx->width * 2, mlx->height * 2);
	ft_memset(ray_img->pixels, 0, ray_img->width * ray_img->height * BPP);
	mlx_image_to_window(mlx,ray_img, x - (ray_img->width / 2), y - (ray_img->height / 2));
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	r = ray_img->height / 2;
	printf("ray len=%d\n", r);
	printf("start (%d, %d)\n", i, j);
	while ( i < (int)ray_img->width)
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		i++;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j--;
		i++;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j < (int)ray_img->height )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j++;
		i++;
	}
	printf("finish (%d, %d)\n", i, j);
	ray_img->dir = 'E';
	return (ray_img);
}

mlx_image_t	*ft_putray_north(mlx_t *mlx, mlx_image_t *player, char **map)
{
	int			x;
	int			y;

	int			i;
	int			j;
	int			r;
	mlx_image_t *ray_img;

	map = NULL;
	x = player->instances[0].x ;
	y = player->instances[0].y ;
	ray_img = mlx_new_image(mlx, mlx->width * 2, mlx->height * 2);
	ft_memset(ray_img->pixels, 0, ray_img->width * ray_img->height * BPP);
	mlx_image_to_window(mlx,ray_img, x - (ray_img->width / 2), y - (ray_img->height / 2));
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	r = ray_img->height / 2;
	printf("ray len=%d\n", r);
	printf("start (%d, %d)\n", i, j);
	while ( j > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j--;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j--;
		i--;
	}
	i = ray_img->width / 2;
	j = ray_img->height / 2;
	while ( j > 0 )
	{
		mlx_put_pixel(ray_img, i, j, 0xFF0000FF);
		j--;
		i++;
	}
	printf("finish (%d, %d)\n", i, j);
	ray_img->dir = 'N';
	return (ray_img);
}

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
	//ft_putgrid(mlx, game->map->map);
	player_map->player_img = ft_putplayer(player_map->mlx, game->map->map);
	player_map->ray_img = ft_putray_north(player_map->mlx, player_map->player_img, game->map->map);
	player_map->map = game->map->map;

	mlx_key_hook(player_map->mlx, &my_keyhook, player_map);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(player_map->mlx);
	mlx_terminate(player_map->mlx);

    return (EXIT_SUCCESS);
}

void	ft_putcolor(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

mlx_image_t	*ft_putplayer(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	char			*line;
	mlx_image_t *player_img;

	x = 0;
	y = 0;
	player_img = mlx_new_image(mlx, 1, 1);
	ft_memset(player_img->pixels, 150, player_img->width * player_img->height * BPP);
	ft_putcolor(player_img);
	mlx_put_pixel(player_img, 150, 150, 0xFF0000FF);
	while (*map != '\0')
	{
		line = *map;
		x = 0;
		while (*line != '\0' && *line != '\n')
		{
			if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			{
				if (*line == 'N')
					player_img->dir = 'N';
				else if (*line == 'S')
					player_img->dir = 'S';
				else if (*line == 'W')
					player_img->dir = 'W';
				else if (*line == 'E')
					player_img->dir = 'E';
				mlx_image_to_window(mlx, player_img, x, y);
			}
			line++;
			x = x + 32;
		}
		y = y + 32;
		map++;
	}
	return (player_img);
}

void	ft_putmap(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	char			*line;
	mlx_image_t	*wall_img;
	mlx_image_t	*space_img;

	x = 0;
	y = 0;
	wall_img = mlx_new_image(mlx, 32, 32);
	space_img = mlx_new_image(mlx, 32, 32);
	ft_memset(wall_img->pixels, 200, wall_img->width * wall_img->height * BPP);
	ft_memset(space_img->pixels, 255, space_img->width * space_img->height * BPP);
	while (*map != '\0')
	{
		line = *map;
		x = 0;
		while (*line != '\0' && *line != '\n')
		{
			if (*line == '1')
				mlx_image_to_window(mlx, wall_img, x, y);
			else if (*line == '0' || *line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
				mlx_image_to_window(mlx, space_img, x, y);
			line++;
			x = x + 32;
		}
		y = y + 32;
		map++;
	}
}

void	ft_putline(int x, int y, mlx_image_t *grid_img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ( i < 32 )
	{
		mlx_put_pixel(grid_img, x + i, y, 0xFF0000FF);
		i++;
	}
}

void	ft_putgrid(mlx_t *mlx, char **map)
{
	int			x;
	int			y;
	int 		i;
	int			j;
	mlx_image_t	*grid_img;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	map = NULL;
	grid_img = mlx_new_image(mlx, mlx->width, mlx->height);
	mlx_image_to_window(mlx, grid_img, x, y);
	while (x < mlx->width)
	{
		y = 0;
		while (y < mlx->height)
		{
			mlx_put_pixel(grid_img, x, y, 0x0000FF);
			y++;
		}
		x = x + 32;
	}
	x = 0;
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			mlx_put_pixel(grid_img, x, y, 0x0000FF);
			x++;
		}
		y = y + 32;
	}
}

int	ft_getwidth(char **map)
{
	int		width;
	int		len;
	char	*line;

	width = 0;
	len = 0;
	while (*map != '\0')
	{
		line = *map;
		len = 0;
		while (*line != '\0' && *line != '\n')
		{
			len++;
			line++;
		}
		if (len > width)
			width = len;
		map++;
	}
	return (width);
}

int	ft_getheight(char **map)
{
	int		height;

	height = 0;
	while (*map != '\0')
	{
		height++;
		map++;
	}
	return (height);
}