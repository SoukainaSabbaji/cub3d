/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/11 15:15:54 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"
#define BPP sizeof(int32_t)
int g_wall_count = 0;


void print_map_array(t_map *map)
{
    int i = 0;
    int j = 0;
    while (i < map->height)
    {
        while (j < map->width)
        {
            printf("%c", map->map[i][j]);
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



void print_wall_coords(t_wall *wall)
{
    int i = 0;
    while (i < g_wall_count)
    {
        printf("x: %d, y: %d\n", wall[i].x, wall[i].y);
        i++;
    }
}

t_wall *fill_map_array(FILE *mapFile, t_map *map)
{
    int i = 0;
    int j = 0;
    char line[255];
    t_wall *wall;

    wall = (t_wall *)malloc(sizeof(t_wall) * 100);
    while (fgets(line, sizeof(line), mapFile))
    {
        while (line[j])
        {
            if (line[j] == ' ' || line[j] == '\n')
                j++;
            else
            {
                map->map[i][j - j / 2] = line[j];
                if (map->map[i][j - j / 2] == '1')
                {
                    wall[g_wall_count].y = (j - j / 2) * WALL_SIZE;
                    wall[g_wall_count].x = i * WALL_SIZE;
                    g_wall_count++;
                }
                j++;
            }
        }
        j = 0;
        i++;
    }
    fclose(mapFile);
    return (wall);
}



//calculate new coordinates x' and y' of a vector (x, y) rotated by angle theta

void rotate_vector(float *x, float *y, float theta)
{
    float x1 = *x;
    float y1 = *y;

    *x = x1 * cos(theta) - y1 * sin(theta);
    *y = x1 * sin(theta) + y1 * cos(theta);
}

//cast a ray from player's position and then rotate the ray by an angle theta

// void    cast_rays(t_coord player_pos)
// {
//     int rays_n = 0;
//     float theta = 60;
//     int i = 0;
//     float rotation_angle = theta / rays_n;
//     rays_n = 100; //screen width normally

//     while (i < rays_n)
//     {
//         rotate_vector(&ray_x, &ray_y, rotation_angle);
//         draw_line(player_pos, (t_coord){player_pos.x + ray_x * 100, player_pos.y + ray_y * 100}, 0x00FF00);
//         i++;
//     }
// }

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
    get_map_dims(mapFile, map);
    map->map = create_map(map->height, map->width);
    g_map = map;
    mapFile = fopen(map_path, "r");
    g_wall = fill_map_array(mapFile, map);
    return (map);
}


bool is_on_wall(int x, int y)
{
    if (g_map->map[y][x] == WALL)
        return (true);
    return (false);
}

void move_player(t_fcoord move)
{
    t_fcoord new_wpos = g_player->world_pos;
    t_coord  new_mpos;

    new_wpos.x += move.x;
    new_wpos.y += move.y;
    new_mpos.x = new_wpos.x;
    new_mpos.y = new_wpos.y;
    if (!is_on_wall(new_mpos.x, new_mpos.y))
    {
        g_player->world_pos = new_wpos;
        g_player->map_pos = new_mpos;
        g_player_img->instances[0].x = new_mpos.x * WALL_SIZE + WALL_SIZE / 2 - PLAYER_SIZE / 2;
        g_player_img->instances[0].y = new_mpos.y * WALL_SIZE + WALL_SIZE / 2 - PLAYER_SIZE / 2;
    }
}

void draw_player(int color, t_coord pos, t_coord mini_map_size, int size)
{
    draw_square(g_player_img, (t_coord){0, 0}, mini_map_size, color, size);
    draw_line(pos, (t_coord){pos.x + size / 2, pos.y * 2 + size / 2}, RAY_COLOR);
    mlx_image_to_window(g_mlx, g_player_img, pos.x, pos.y);
    // cast_rays((t_coord){pos.x + size / 2, pos.y + size / 2});
}



void draw_map(mlx_t *mlx, t_map *map, t_coord mini_map_size)
{

    int square_size = min(mini_map_size.x / map->width, mini_map_size.x / map->height);
    int player_size = square_size / 3;
    int i = 0;
    int j = 0;

    g_img = mlx_new_image(mlx, mini_map_size.x, mini_map_size.y);
    g_player = (t_player *)malloc(sizeof(t_player));
    while (i < map->height)
    {
        while (j < map->width)
        {
            if (map->map[i][j] == WALL)
            {
                t_coord wall_pos = (t_coord){.x = j * square_size,
                                            .y = i * square_size};
                draw_square(g_img, wall_pos, mini_map_size, MMAP_WALL_COLOR, square_size);
            }
            if (map->map[i][j] == PLAYER)
            {
                g_player_img = mlx_new_image(mlx, player_size, player_size);
                g_player->world_pos = (t_fcoord){.x = j + .5, .y = i + .5};
                g_player->map_pos   = (t_coord){.x = j, .y = i};                
                g_player->img = g_player_img;
                
                t_coord player_pos = (t_coord){.x = g_player->world_pos.x * square_size - player_size / 2,
                                            .y = g_player->world_pos.y * square_size - player_size / 2};
                draw_player(PLAYER_COLOR, player_pos,mini_map_size, player_size);
            }
            j++;
        }
        j = 0;
        i++;
    }
}


int32_t main()
{
    t_map *map;

    map = get_map("/Users/ssabbaji/Desktop/cub3d/maptest.txt");
    print_map_array(map);    
    g_mlx = mlx_init(map->width * WALL_SIZE, map->height * WALL_SIZE, "42pelotas", true);
    if (!g_mlx)
        ft_error();
    draw_map(g_mlx, map, (t_coord){map->width * WALL_SIZE, map->height * WALL_SIZE});
    mlx_image_to_window(g_mlx, g_img, 0, 0);
    mlx_loop_hook(g_mlx, &hook, g_mlx);
    mlx_loop_hook(g_mlx, &hook_2, g_mlx);
    mlx_loop(g_mlx);
    mlx_terminate(g_mlx);
    return (EXIT_SUCCESS);
}
