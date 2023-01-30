#include "../includes/minimap.h"

static void get_map_dims(FILE *mapFile, t_map *map)
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
    map->height = lines;
    map->width = columns;
}

static int check_map_chars(t_map *map)
{
   t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (map->map[i][j] != WALL && \
                map->map[i][j] != EMPTY && \
                map->map[i][j] != 'W' && \
                map->map[i][j] != 'S' && \
                map->map[i][j] != 'E' && \
                map->map[i][j] != 'N' && \
                map->map[i][j] != ' ')
                return (0);
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}

static int check_map_walls(t_map *map)
{
    t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (iter.i == 0 || iter.i == map->height - 1)
            {
                if (map->map[i][j] != WALL)
                    return (0);
            }
            else if (iter.j == 0 || iter.j == map->width - 1)
            {
                if (map->map[i][j] != WALL)
                    return (0);
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}

//next function checks if a wall is enclosed 

static int check_map_enclosed(t_map *map)
{
    t_iter iter;

    while (iter.i < map->height)
    {
        while (iter.j < map->width)
        {
            if (map->map[i][j] == WALL)
            {
                if (map->map[i - 1][j] == EMPTY || \
                    map->map[i + 1][j] == EMPTY || \
                    map->map[i][j - 1] == EMPTY || \
                    map->map[i][j + 1] == EMPTY)
                    return (0);
            }
            iter.j++;
        }
        iter.j = 0;
        iter.i++;
    }
    return (1);
}