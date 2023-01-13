/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/12 18:05:16 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

void    get_map_dims(FILE *mapFile, int *height , int *width)
{
    int lines = 0;
    int columns = 0;
    char line[255];

    if (mapFile == NULL)
        return ;
    fgets(line, sizeof(line), mapFile);
    if (strlen(line))
    {
        columns = strlen(line) - 1;
        lines++;
    }
    while (fgets(line, sizeof(line), mapFile)) 
        lines++;
    fclose(mapFile);
    *height = lines;
    *width = columns;
}

int **create_map(FILE *mapFile, int MAP_HEIGHT, int MAP_WIDTH)
{
    int **map;

    map = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++) 
        map[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
    for (int i = 0; i < MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH; j++) 
            fscanf(mapFile, "%d", &map[i][j]);
    }
    return (map);
}


void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < cube->map->width && y > 0 && y < cube->map->height)
	{
		dst = cube->img_data + (y * cube->line_size
				+ x * (cube->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// void    draw_cube(t_cube *cube)
// {
    
// }

void drawMap(t_cube *cube, t_map *map) 
{
    for (int i = 0; i < map->height; i++) 
    {
        for (int j = 0; j < map->width; j++) 
        {
            if (map->map[i][j] == 1) 
                my_mlx_pixel_put(cube, j, i, 0xFFFFFF);
            else 
                my_mlx_pixel_put(cube, j, i, 0x000000);
        }
    }
}


t_cube  *init_cube(t_cube *cube)
{
    cube = (t_cube *)malloc(sizeof(t_cube));
    cube->img_data = mlx_get_data_addr(cube->img_ptr, &(cube->bpp),
			&(cube->line_size), &(cube->endian));
    cube->mlx = mlx_init();
    cube->win = mlx_new_window(cube->mlx, 500, 500, "Hello world!");
    cube->bpp = 32;
    cube->line_size = 500 * 4;
    cube->endian = 0;
    return (cube);
}

int main()
{
    int MAP_HEIGHT = 0;
    int MAP_WIDTH = 0;
    int     **map;
    t_map   *map_data;
    t_cube  *cube;
    
    
    cube = init_cube(cube);
    FILE* mapFile = fopen("maptest.txt", "r");
    map_data = (t_map *)malloc(sizeof(t_map));
    get_map_dims(mapFile,&MAP_HEIGHT, &MAP_WIDTH);
    map = create_map(mapFile, MAP_HEIGHT, MAP_WIDTH);
    map_data->map = map;
    map_data->height = MAP_HEIGHT;
    map_data->width = MAP_WIDTH;
    drawMap(cube, map_data);
    mlx_loop(cube->mlx);
    // printf("MAP_HEIGHT = %d, MAP_WIDTH = %d\n", MAP_HEIGHT, MAP_WIDTH);
}
