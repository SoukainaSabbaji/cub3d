/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makacem <makacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/20 11:27:53 by makacem          ###   ########.fr       */
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


void    cast_rays(t_player *player,  t_coord dims)
{
    int rays_n = 0;
    int i = 0;
    rays_n = 480; //screen width normally
    
    g_player->fov = 60;
    float theta = g_player->fov * M_PI / 180; //convert radians to degrees
    float rotation_angle = theta / rays_n;
    float ray_x = player->camera_plane.x;
    float ray_y = player->camera_plane.y;
    // float ray_x = player->world_pos.x;
    // float ray_y = player->world_pos.y;
    rotate_vector(&ray_x, &ray_y, 30); //we rotate the ray by 30 degrees to the left so we can start from there
    while (i < rays_n)
    {
        rotate_vector(&ray_x, &ray_y, rotation_angle);
        draw_line(player->camera_plane, (t_coord){player->camera_plane.x + ray_x, player->camera_plane.y + ray_y}, RAY_COLOR, dims);
        i++;
    }
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
    map->map_file = mapFile;
    get_map_dims(map);
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
        // g_player->camera_plane.x = g_player->world_pos.x + g_player->camera_
        // g_player->camera_plane.x = g_player->world_pos.x ;
        // g_player->camera_plane.y = g_player->world_pos.y ;
        cast_rays(g_player, (t_coord){640, 512});
        g_player_img->instances[0].x = new_mpos.x * WALL_SIZE + WALL_SIZE / 2 - PLAYER_SIZE / 2;
        g_player_img->instances[0].y = new_mpos.y * WALL_SIZE + WALL_SIZE / 2 - PLAYER_SIZE / 2;
    }
}

t_coord *rotate_player(t_coord *points, int num_points,float angle)
{
    float cos_theta = 0;
    float sin_theta = 0;
    t_coord point;
   
    int i = 0;
    int x = 0;
    int y = 0;
    
    angle = angle * M_PI / 180;
    cos_theta = cos(angle);
    sin_theta = sin(angle);
    while (i < num_points)
    {
        point = points[i];
        x = point.x;
        y = point.y;
        
        points[i].x = cos_theta * x - sin_theta * y;
        points[i].y = sin_theta * x + cos_theta * y;
        i++;
    }
    return (points);
}

void call_hooks()
{
    mlx_loop_hook(g_mlx, &hook, g_mlx);
    mlx_loop_hook(g_mlx, &hook_2, g_mlx);
}


void    print_coords(t_coord *points)
{
    int i = 0;
    while (i < 64)
    {
        printf("x : %d, y : %d\n", points[i].x, points[i].y);
        i++;
    }
}

void draw_player(t_coord pos, t_coord mini_map_size, int size)
{
    t_coord camera_pos;
    t_coord *points = NULL;

    points = (t_coord *)calloc(size * size, sizeof(t_coord));
    printf("number of pixels : %d\n",size *size);
    camera_pos.x = pos.x + size / 2;
    camera_pos.y = pos.y + size / 2;
    g_player->camera_plane = camera_pos;
    cast_rays(g_player, mini_map_size);
    points = draw_square(points, g_player_img, (t_coord){0, 0}, mini_map_size, PLAYER_COLOR, size);
    points = rotate_player(points, size * size, 20);
    // print_coords(points);
    // draw_square_2(points, g_player_img, MMAP_WALL_COLOR, size);
    call_hooks();
    mlx_image_to_window(g_mlx, g_player_img, pos.x, pos.y);
}


void draw_map(mlx_t *mlx, t_map *map, t_coord mini_map_size)
{

    int square_size = min(mini_map_size.x / map->width, mini_map_size.x / map->height);
    int player_size = square_size / 3;
    int i = 0;
    int j = 0;
    t_coord player_pos;

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
                draw_square(NULL, g_img, wall_pos, mini_map_size, MMAP_WALL_COLOR, square_size - 1);
            }
            if (map->map[i][j] != WALL)
            {
                t_coord empty_pos = (t_coord){.x = j * square_size,
                                            .y = i * square_size};
                draw_square(NULL,g_img, empty_pos, mini_map_size, MMAP_EMPTY_COLOR, square_size - 1);
            }
            if (map->map[i][j] == PLAYER)
            {
                printf("player found at i:%d j:%d\n", i , j);
                g_player_img = mlx_new_image(mlx, player_size, player_size);
                g_player->world_pos = (t_fcoord){.x = j + .5, .y = i + .5};
                g_player->map_pos   = (t_coord){.x = j, .y = i};                
                g_player->img = g_player_img;
                
                player_pos = (t_coord){.x = g_player->world_pos.x * square_size - player_size / 2,
                                            .y = g_player->world_pos.y * square_size - player_size / 2};
                printf("player_pos.x:%d player_pos.y:%d\n", player_pos.x, player_pos.y);
            }
            j++;
        }
        j = 0;
        i++;
    }
    draw_player(player_pos,mini_map_size, 8);
}
