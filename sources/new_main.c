/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:57:45 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/03/05 17:57:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

mlx_image_t	*g_img;

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
            printf("%c ", map->map[i][j]);
            j++;
        }
        j = 0;
        i++;
    }
}

int **create_map(int MAP_HEIGHT, int MAP_WIDTH)
{
    int **map;

    map = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++) 
        map[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            map[i][j] = 0;
        }
    }
    return (map);
}

void    fill_map_array(FILE *mapFile, t_map *map)
{
    int i = 0;
    int j = 0;
    char line[255];

    while (fgets(line, sizeof(line), mapFile))
    {
        while (j < map->width)
        {
            map->map[i][j] = line[j] - '0';
            j++;
        }
        j = 0;
        i++;
    }
    fclose(mapFile);
}

t_map   *get_map(char *map_path)
{
    FILE *mapFile;
    t_map *map;

    map = (t_map *)malloc(sizeof(t_map));
    mapFile = fopen(map_path, "r");
    get_map_dims(mapFile, &map->height, &map->width);
    map->map = create_map(map->height, map->width);
    mapFile = fopen(map_path, "r");
    fill_map_array(mapFile, map);
    return (map);
}

void    draw_map(t_map *map)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    int color = 0;

    while (i < map->height)
    {
        while (j < map->width)
        {
            if (map->map[i][j] == 1)
                color = 0x000000;
            else
                color = 0xFFFFFF;
            while (x < 10)
            {
                while (y < 10)
                {
                    mlx_pixel_put(g_img, x + (j * 10), y + (i * 10), color);
                    y++;
                }
                y = 0;
                x++;
            }
            x = 0;
            j++;
        }
        j = 0;
        i++;
    }
}

int     main(int argc, char **argv)
{
    t_map *map;

    if (argc != 2)
        return (0);
    map = get_map(argv[1]);
    // print_map_array(map);
    draw_map(map);
    return (0);
}