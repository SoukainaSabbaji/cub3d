/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:52:54 by ssabbaji          #+#    #+#             */
/*   Updated: 2023/02/07 13:43:47 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minimap.h"
#define BPP sizeof(int32_t)

mlx_image_t *g_img;
mlx_image_t *g_player_img;
mlx_t *g_mlx;
int g_wall_count = 0;
t_player *g_player;
t_wall *g_wall;
t_map *g_map;

void ft_putstr_fd(const char *s, int fd)
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

void hook_2(void *param)
{
    mlx_t *mlx;

    mlx = param;
    //change angles after moving the player 
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        move_player((t_fcoord){0, -0.1});
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        move_player((t_fcoord){0, 0.1});
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        move_player((t_fcoord){-0.1, 0});
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        move_player((t_fcoord){0.1, 0});
    
}

void draw_line(t_coord p1, t_coord p2, int color)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = 0;
    float x = p1.x + 0.5;
    float y = p1.y + 0.5;
    int i = 0;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    while (i <= steps)
    {
        mlx_put_pixel(g_img,x, y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}




void draw_player(int color, t_coord pos, t_coord mini_map_size, int size)
{
    draw_square(g_player_img, (t_coord){0, 0}, mini_map_size, color, size);
    draw_line((t_coord){pos.x, pos.y}, (t_coord){pos.x + size, pos.y + size}, PLAYER_COLOR);
    draw_line((t_coord){pos.x + size, pos.y}, (t_coord){pos.x, pos.y + size * 2}, PLAYER_COLOR);
    mlx_image_to_window(g_mlx, g_player_img, pos.x, pos.y);
}

void draw_square(mlx_image_t *img, t_coord pos, t_coord dims, int color, int size)
{
    int i = 0;
    int j = 0;

    while (i < size)
    {
        while (j < size)
        {
            int nx = pos.x + i;
            int ny = pos.y + j;
            if (nx >= 0 && nx < dims.x && ny >= 0 && ny < dims.y)
                mlx_put_pixel(img, nx, ny, color);
            j++;
        }
        j = 0;
        i++;
    }
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

    map = get_map("/Users/ssabbaji/Desktop/ngpl/maptest.txt");
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
