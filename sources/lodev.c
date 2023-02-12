#include "../includes/minimap.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

void memset_pixel(void *image, int x, int y, int color)
{
    int *img = (int*)image;
    int size = screenWidth * screenHeight;
    int index = y * screenWidth + x;

    if (index >= 0 && index < size)
        memset(img + index, color, sizeof(int));
}

int worldMap[mapWidth][mapHeight] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// int main(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;
//     double posX = 22, posY = 12;
//     double dirX = -1, dirY = 0;
//     double planeX = 0, planeY = 0.66;
//     void *mlx_ptr = NULL;
//     // void *win_ptr;
//     // int bpp = sizeof(int32_t);
//     // int size_line = 0;
//     // int endian = 0;
//     unsigned char texture[10][256][256];
//     int textureHeight = 256;
//     int textureWidth = 256;
//     mlx_image_t *g_img = NULL;

//     g_mlx = mlx_init(mapWidth * 64, mapHeight * 64, "42pelotas", NULL);
//     // win_ptr = mlx_new_window(mlx_ptr, screenWidth, screenHeight, "Raycaster");
//     // img_ptr = mlx_new_image(mlx_ptr, screenWidth, screenHeight);
//     // get the  value of img_ptr using something else other than mlx_new_image
//     // mlx_image_t *img_ptr = mlx_new_image(mlx_ptr, screenWidth, screenHeight);
//     // char *data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

//     int x;
//     for (x = 0; x < screenWidth; x++)
//     {
//         double cameraX = 2 * x / (double)screenWidth - 1;

//         double rayDirX = dirX + planeX * cameraX;
//         double rayDirY = dirY + planeY * cameraX;
//         int mapX = (int)posX;
//         int mapY = (int)posY;

//         double sideDistX;
//         double sideDistY;

//         double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//         double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

//         double perpWallDist;
//         int stepX;
//         int stepY;

//         int hit = 0;
//         int side;
//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (posX - mapX) * deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//         }
//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (posY - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//         }
//         while (hit == 0)
//         {
//             if (sideDistX < sideDistY)
//             {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             }
//             else
//             {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }
//             if (worldMap[mapX][mapY] > 0)
//                 hit = 1;
//         }
//         if (side == 0)
//             perpWallDist = (sideDistX - deltaDistX);
//         else
//             perpWallDist = (sideDistY - deltaDistY);
//         int lineHeight = (int)(screenHeight / perpWallDist);
//         int drawStart = -lineHeight / 2 + screenHeight / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = lineHeight / 2 + screenHeight / 2;
//         if (drawEnd >= screenHeight)
//             drawEnd = screenHeight - 1;
//         int color = worldMap[mapX][mapY] - 1;
//         int textureX = (int)(perpWallDist * textureWidth);
//         if (side == 0 && rayDirX > 0)
//             textureX = textureWidth - textureX - 1;
//         if (side == 1 && rayDirY < 0)
//             textureX = textureWidth - textureX - 1;

//         int y;

//         // for (y = drawStart; y < drawEnd; y++)
//         // {
//         //     int d = y * 256 - screenHeight * 128 + lineHeight * 128;
//         //     int textureY = ((d * textureHeight) / lineHeight) / 256;
//         //     int texturePixel = (textureY * textureWidth + textureX) * 4;
//         //     unsigned char red = (unsigned char) texture[texturePixel];
//         //     unsigned char green = (unsigned char) texture[texturePixel + 1];
//         //     unsigned char blue = (unsigned char) texture[texturePixel + 2];
//         //     int pixel = (y * size_line + x * bpp / 8);

//         //     char *data = mlx_get_data_addr(g_img, &bpp, &size_line, &endian);
//         //     data[pixel] = blue;
//         //     data[pixel + 1] = green;
//         //     data[pixel + 2] = red;
//         // }

//         for (y = drawStart; y < drawEnd; y++)
//         {
//             int d = y * 256 - screenHeight * 128 + lineHeight * 128;
//             int textureY = ((d * textureHeight) / lineHeight) / 256;
//             int texturePixel = (textureY * textureWidth + textureX) * 4;
//             // unsigned char red = (unsigned char)texture[texturePixel];
//             // unsigned char green = (unsigned char)texture[texturePixel + 1];
//             // unsigned char blue = (unsigned char)texture[texturePixel + 2];
//             int pixelX = x;
//             int pixelY = y;

//             // mlx_put_pixel(g_img, pixelX, pixelY, red);
//             memset_pixel(g_img, pixelX, pixelY, color);
//         }
//     }
//     mlx_image_to_window(g_mlx, g_img, 0, 0);
//     mlx_loop(mlx_ptr);
//     return (0);
// }