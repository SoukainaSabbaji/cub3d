/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/17 16:05:33 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"


mlx_image_t *g_img;


int min(int a, int b)
{
    return (a < b) ? a : b;
}

void get_map_dims(FILE *mapFile, int *height, int *width)
{
    int lines = 0;
    int columns = 0;
    char line[255];

    if (mapFile == NULL)
        return;
    fgets(line, sizeof(line), mapFile);
    int i = 0;
    if (strlen(line))
    {
        while (i < (int)strlen(line))
        {
            if (line[i] == '0' || line[i] == '1')
                columns++;
            i++;
        }
        lines++;
    }
    while (fgets(line, sizeof(line), mapFile))
        lines++;
    fclose(mapFile);
    *height = lines;
    *width = columns;
}

void print_map_array(t_map *map)
{
    int i = 0;
    int j = 0;
    while (i < map->height)
    {
        while (j < map->width)
        {
            printf("%c ", map->map[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}

char **create_map(int MAP_HEIGHT, int MAP_WIDTH)
{
    char **map;
    int i = 0;
    int j = 0;

    map = (char **)malloc(sizeof(char *) * MAP_HEIGHT);
    if (map == NULL)
        return (NULL);
    while (i < MAP_HEIGHT)
    {
        map[i] = (char *)malloc(sizeof(char) * MAP_WIDTH);
        if (map[i] == NULL)
            return (NULL);
        i++;
    }
    i = 0;
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            map[i][j] = '0';
            j++;
        }
        i++;
    }
    return (map);
}

void fill_map_array(FILE *mapFile, t_map *map)
{
    int i = 0;
    int j = 0;
    char line[255];

    while (fgets(line, sizeof(line), mapFile))
    {
        while (line[j])
        {
            if (line[j] == ' ' || line[j] == '\n')
                j++;
            else
            {
                // there's a huge ass trqi3a here fix it later
                map->map[i][j - j / 2] = line[j];
                j++;
            }
        }
        j = 0;
        i++;
    }
    fclose(mapFile);
}

t_map *get_map(char *map_path)
{
    FILE *mapFile;
    t_map *map;

    map = (t_map *)calloc(1, sizeof(t_map));
    if (map == NULL)
        return (NULL);
    mapFile = fopen(map_path, "r");
    if (mapFile == NULL)
    {
        printf("Error: fopen() failed\n");
        return (NULL);
    }
    get_map_dims(mapFile, &map->height, &map->width);
    map->map = create_map(map->height, map->width);
    mapFile = fopen(map_path, "r");
    fill_map_array(mapFile, map);
    return (map);
}

void draw_square(int color, int x, int y, int size)
{
    int i = 0;
    int j = 0;
    
    while (i < size)
    {
        while (j < size)
        {
            // printf("x: %d, y: %d\n",x ,y );
            // printf("x: %d, y: %d\n",x + i ,y + j );
            mlx_put_pixel(g_img, x+i , y+j , color);
            j++;
        }
        j = 0;
        i++;
    }
}

void draw_map(t_map *map, int win_width, int win_height)
{
    // int square_size = min(win_width / map->width, win_height / map->height);
    int square_size = 64;
    int color = 0;
    int i = 0;
    int j = 0;
    (void)win_height;
    (void)win_width;
    
    while (i < map->height)
    {
        while (j < map->width)
        {
            if (map->map[i][j] == '1')
                color = 0xFFFFFFFF;
            else if (map->map[i][j] == '0')
                color = 0x00000000;
            int x = j * square_size;
            int y = i * square_size;
            draw_square(color, x, y, square_size);
            j++;
        }
        j = 0;
        i++;
    }
}

t_cube *init_cube(t_cube *cube)
{
    cube = (t_cube *)malloc(sizeof(t_cube));
    cube->mlx = mlx_init(cube->map->width, cube->map->height, "Hello world!", true);
    if (cube->mlx == NULL)
    {
        printf("Error: mlx_init() failed\n");
        return (NULL);
    }
    cube->img_ptr = mlx_new_image(cube->mlx, 500, 500);
    memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
    return (cube);
}

int32_t main()
{
    mlx_t *mlx;
    t_map *map;

    map = get_map("/Users/ssabbaji/Desktop/cub3d/maptest.txt");
    print_map_array(map);
    mlx = mlx_init(map->height * 64, map->width * 64, "MLX42", true);
    if (!mlx)
        exit(EXIT_FAILURE);
    g_img = mlx_new_image(mlx, 128, 128); 
    // memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
    draw_map(map, map->height * 64, map->width * 64);
    mlx_image_to_window(mlx, g_img, 0, 0);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
