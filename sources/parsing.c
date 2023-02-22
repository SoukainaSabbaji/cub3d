/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:51:48 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/31 11:51:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"

// void get_map_dims(t_map *map)
// {
//     int lines = 0;
//     int columns = 0;
//     char line[255];

//     if (map->map_file == NULL)
//         return;
//     fgets(line, sizeof(line), map->map_file);
//     int i = 0;
//     if (strlen(line))
//     {
//         while (i < (int)strlen(line))
//         {
//             if (line[i] == '0' || line[i] == '1')
//                 columns++;
//             i++;
//         }
//         lines++;
//     }
//     while (fgets(line, sizeof(line), mapFile))
//         lines++;
//     fclose(mapFile);
//     map->height = lines;
//     map->width = columns;
// }

int check_map_chars(t_map *map)
{
   t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (map->map[iter.i][iter.j] != WALL && \
                map->map[iter.i][iter.j] != EMPTY && \
                map->map[iter.i][iter.j] != 'W' && \
                map->map[iter.i][iter.j] != 'S' && \
                map->map[iter.i][iter.j] != 'E' && \
                map->map[iter.i][iter.j] != 'N' && \
                map->map[iter.i][iter.j] != ' ')
                return (0);
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}

int check_map_walls(t_map *map)
{
    t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (iter.i == 0 || iter.i == map->height - 1)
            {
                if (map->map[iter.i][iter.j] != WALL)
                    return (0);
            }
            else if (iter.j == 0 || iter.j == map->width - 1)
            {
                if (map->map[iter.i][iter.j] != WALL)
                    return (0);
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}


int check_map_enclosed(t_map *map)
{
    t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (map->map[iter.i][iter.j] == WALL)
            {
                if (map->map[iter.i - 1][iter.j] == EMPTY || \
                    map->map[iter.i + 1][iter.j] == EMPTY || \
                    map->map[iter.i][iter.j - 1] == EMPTY || \
                    map->map[iter.i][iter.j + 1] == EMPTY)
                    return (0);
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}

int count_walls(FILE *mapFile)
{
    int i = 0;
    int j = 0;
    int count = 0;
    char line[255];

    while (fgets(line, sizeof(line), mapFile))
    {
        while (line[j])
        {
            if (line[j] != ' ' && line[j] != '\n')
            {
                if (line[j] == WALL)
                    count++;
                j++;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (count);
}