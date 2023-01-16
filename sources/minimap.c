/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/16 14:34:49 by ssabbaji         ###   ########.fr       */
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

void    print_map_array(t_map *map)
{
    int i = 0;
    int j = 0;
    while (i < map->height)
    {
        while (j < map->width)
        {
            printf("%d ", map->map[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}

int **create_map(FILE *mapFile, int MAP_HEIGHT, int MAP_WIDTH)
{
    int **map;

    map = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++) 
        map[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
    rewind(mapFile); // set the file pointer back to the beginning of the file
    for (int i = 0; i < MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            char c;
            while ((c = fgetc(mapFile)) != EOF) // read one character at a time
            {
                if (c == '1' || c == '0') // if the character is a '1' or '0'
                {
                    ungetc(c, mapFile); // push the character back to the file
                    fscanf(mapFile, "%d", &map[i][j]); // read the integer
                    break;
                }
            }
        }
    }
    fclose(mapFile);
    return (map);
}





void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= cube->map->width || y < 0 || y >= cube->map->height) 
    {
        printf("Error: Invalid pixel coordinates (x = %d, y = %d)\n", x, y);
        return;
    }
    dst = cube->img_data + (y * cube->line_size + x * (cube->bpp / 8));
    *(unsigned int *)dst = color;
}

// void    draw_cube(t_cube *cube)
// {
    
// }

// void drawMap(t_cube *cube, t_map *map) 
// {
//     if (cube == NULL || cube->map == NULL) 
//     {
//         printf("Error: cube or cube->map is null\n");
//         return;
//     }
//     for (int i = 0; i < map->height; i++) 
//     {
//         for (int j = 0; j < map->width; j++) 
//         {
//             if (map->map[i][j] == 1) 
//                 my_mlx_pixel_put(cube, j, i, 0xFFFFFF);
//             else 
//                 my_mlx_pixel_put(cube, j, i, 0x000000);
//         }
//     }
// }

void drawMap(t_cube *cube, t_map *map) 
{
    int i = 0;
    int j = 0;
    print_map_array(map);
    if (cube == NULL || cube->map == NULL) 
    {
        printf("Error: cube or cube->map is null\n");
        return;
    }
    while (i < map->height)
    {
        while (j < map->width)
        {
            int color;
            if (map->map[i][j] == 1)
            {
                printf("color\n");
                color = 0x001da32d;
            } 
            else 
                color = 0x00a31d1d;
            for (int k = 0; k < 10; k++) 
            {
                for (int l = 0; l < 10; l++) 
                {
                    // my_mlx_pixel_put(cube, j*10 + k, i*10 + l, color);
                    mlx_pixel_put(cube->mlx, cube->win, j*10 + k, i*10 + l, color);
                    // printf("x = %d, y = %d, color = %d\n", j*10 + k, i*10 + l, color);
                }
            }
            j++;
        }
        i++;
    }
} 



t_cube  *init_cube(t_cube *cube)
{
    cube = (t_cube *)malloc(sizeof(t_cube));
    cube->mlx = mlx_init();
    if (cube->mlx == NULL)
    {
        printf("Error: mlx_init() failed\n");
        return (NULL);
    }
    cube->img_ptr = mlx_new_image(cube->mlx, 500, 500);
    cube->img_data = mlx_get_data_addr(cube->img_ptr, &(cube->bpp), &(cube->line_size), &(cube->endian));
    cube->win = mlx_new_window(cube->mlx, 500, 500, "Hello world!");
    return (cube);
}

// int main()
// {
//     int MAP_HEIGHT = 0;
//     int MAP_WIDTH = 0;
//     int     **map;
//     t_map   *map_data;
//     t_cube  *cube;
    
    
//     cube = init_cube(NULL);
//     FILE *mapFile = fopen("maptest.txt", "r");
//     if (mapFile == NULL) 
//     {
//         printf("Error: Invalid map file");
//         return 1;
//     }
//     map_data = (t_map *)malloc(sizeof(t_map));
//     get_map_dims(mapFile,&MAP_HEIGHT, &MAP_WIDTH);
//     if (MAP_HEIGHT <= 0 || MAP_WIDTH <= 0) 
//     {
//         printf("Error: Invalid map dimensions (height = %d, width = %d)\n", MAP_HEIGHT, MAP_WIDTH);
//         return 1;
//     }
//     map = create_map(mapFile, MAP_HEIGHT, MAP_WIDTH);
//     fclose(mapFile);
//     map_data->map = map;
//     map_data->height = MAP_HEIGHT;
//     map_data->width = MAP_WIDTH;
//     drawMap(cube, map_data);
//     mlx_put_image_to_window(cube->mlx, cube->win, cube->img_ptr, 0, 0);
//     mlx_loop(cube->mlx);
//     // printf("MAP_HEIGHT = %d, MAP_WIDTH = %d\n", MAP_HEIGHT, MAP_WIDTH);
// }


int main()
{
    int MAP_HEIGHT = 0;
    int MAP_WIDTH = 0;
    int     **map;
    t_map   *map_data;
    t_cube  *cube;
    
    
    cube = init_cube(NULL);
    FILE *mapFile = fopen("maptest.txt", "r");
    if (mapFile == NULL) 
    {
        printf("Error: Invalid map file");
        return 1;
    }
    map_data = (t_map *)malloc(sizeof(t_map));
    get_map_dims(mapFile,&MAP_HEIGHT, &MAP_WIDTH);
    if (MAP_HEIGHT <= 0 || MAP_WIDTH <= 0) 
    {
        printf("Error: Invalid map dimensions (height = %d, width = %d)\n", MAP_HEIGHT, MAP_WIDTH);
        return 1;
    }
    map = create_map(mapFile, MAP_HEIGHT, MAP_WIDTH);
    fclose(mapFile);
    map_data->map = map;
    map_data->height = MAP_HEIGHT;
    map_data->width = MAP_WIDTH;
    drawMap(cube, map_data);
    if (cube->img_ptr == NULL)
        printf("img_ptr is null\n");
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img_ptr, 500, 500);
    mlx_loop(cube->mlx);
    // printf("MAP_HEIGHT = %d, MAP_WIDTH = %d\n", MAP_HEIGHT, MAP_WIDTH);
}
