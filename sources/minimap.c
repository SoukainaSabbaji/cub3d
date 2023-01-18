/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/01/18 17:20:44 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"
#define BPP sizeof(int32_t)

mlx_image_t *g_img;
mlx_image_t *g_player;
mlx_t *g_mlx;
int g_wall_count = 0;



void    ft_putstr_fd(const char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
    {
        write(fd, &s[i], 1);
        i++;
    }
}

static void ft_error(void)
{
    ft_putstr_fd(mlx_strerror(mlx_errno), 2);
    exit(EXIT_FAILURE);
}

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
                // there's a huge ass trqi3a here fix it later
                // j -= j/2;
                map->map[i][j - j / 2] = line[j];
                if (map->map[i][j - j / 2] == '1')
                {
                    wall[g_wall_count].x = (j - j / 2) * 64; 
                    wall[g_wall_count].y = i * 64;
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

void    print_wall_coords(t_wall *wall)
{
    int i = 0;
    while (i < g_wall_count)
    {
        printf("x: %d, y: %d\n", wall[i].x, wall[i].y);
        i++;
    }
}

t_map *get_map(char *map_path)
{
    FILE *mapFile;
    t_map *map;
    t_wall *wall;
    
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
    wall = fill_map_array(mapFile, map);
    print_wall_coords(wall);
    return (map);
}

void hook_2(void *param)
{
    mlx_t *mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        g_player->instances[0].y -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        g_player->instances[0].y += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        g_player->instances[0].x -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        g_player->instances[0].x += 5;
}

// void draw_player(int color, int x, int y, int size)
// {
//     int i = 0;
//     int j = 0;

//     while (i < size)
//     {
//         while (j < size)
//         {
//             printf("alo\n");
//             mlx_put_pixel(g_player, x, y, color);
//             j++;
//         }
//         j = 0;
//         i++;
//     }
//     mlx_image_to_window(g_mlx, g_player, 200, 200);
//     mlx_loop_hook(g_mlx, &hook_2, g_mlx);
// }


// static int get_rgba(int r, int g, int b, int a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

void draw_player(int color, int x, int y, int size)
{
    (void)color;
    (void)size;
    
    memset(g_player->pixels, 250, 16 * 16 * BPP);
    mlx_image_to_window(g_mlx, g_player, x, y);
    mlx_loop_hook(g_mlx, &hook_2, g_mlx);
}

void draw_square(int color, int x, int y, int size, int win_width, int win_height)
{

    int i = 0;
    int j = 0;

    if (color == 0x00ffffff)
    {
        size /= 4;
        draw_player(color, x, y, size);
        return ;
    }
    while (i < size)
    {
        while (j < size)
        {
            int nx = x + i;
            int ny = y + j;
            if (nx > 0 && nx < win_width && ny > 0 && ny < win_height)
                mlx_put_pixel(g_img, nx, ny, color);
            j++;
        }
        j = 0;
        i++;
    }
}

void draw_map(mlx_t *mlx, t_map *map, int win_width, int win_height)
{
    int square_size = min(win_width / map->width, win_height / map->height);
    // int square_size = 64;
    int color = 0;
    int i = 0;
    int j = 0;

    g_img = mlx_new_image(mlx, win_width, win_height);
    while (i < map->height)
    {
        while (j < map->width)
        {
            if (map->map[i][j] == '1')
                color = 0xFFFFFFFF;
            else if (map->map[i][j] == '0')
                color = 0x00000000;
            else if (map->map[i][j] == 'P')
            {
                color = 0x00ffffff;
                g_player = mlx_new_image(mlx, 16, 16);
            }
            int x = j * square_size;
            int y = i * square_size;
            draw_square(color, x, y, square_size, win_width, win_height);
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

void hook(void *param)
{
    mlx_t *mlx;

    mlx = param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
}

int32_t main()
{
    t_map *map;

    map = get_map("/Users/ssabbaji/Desktop/cub3d/maptest.txt");
    print_map_array(map);
    g_mlx = mlx_init(map->width * 64, map->height * 64, "MLX42", true);
    if (!g_mlx)
       ft_error();
    g_img = mlx_new_image(g_mlx, 128, 128);
    // memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
    draw_map(g_mlx, map, map->height * 64, map->width * 64);
    mlx_image_to_window(g_mlx, g_img, 0, 0);
    mlx_loop_hook(g_mlx, &hook, g_mlx);
    mlx_loop(g_mlx);
    mlx_terminate(g_mlx);
    printf("wall count :%d\n", g_wall_count);
    return (EXIT_SUCCESS);
}
