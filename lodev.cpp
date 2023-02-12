
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

// place the example code below here:

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

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

int main(int /*argc*/, char * /*argv*/[])
{
  double posX = 22, posY = 12;      // x and y start position , start position of the player
  double dirX = -1, dirY = 0;       // initial direction vector , -1 to the left and up
  double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane , 0.66 = 66°

  double time = 0;    // time of current frame , also called delta time , cuz its also a derivative of time
  double oldTime = 0; // time of previous frame

  screen(screenWidth, screenHeight, 0, "Raycaster"); // sdl function to create a window
  while (!done())
  {
    for (int x = 0; x < w; x++)
    {
      // calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space , we normalize the x coordinate to be between -1 and 1
                                              //  so we start from the left of the screen and go to the right
      // so the camera is always centered on the player
      double rayDirX = dirX + planeX * cameraX; // ray direction for each x-coordinate , we add the camera plane to the direction vector
                                                // raydir is the direction of the ray , it is the direction of the player plus the direction of the camera plane
      double rayDirY = dirY + planeY * cameraX; // same thing for the y coordinate
                                                // this grants us the position of the player in the camera space

      // which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      // length (magnitude) of ray from current position to next x or y-side
      // every ray has sideDistX and sideDistY , they are the distance to the next x or y side
      double sideDistX;
      double sideDistY;

      // length of ray from one x or y-side to next x or y-side
      // these are derived as:
      // deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      // deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      // which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      // where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      // unlike (dirX, dirY) is not 1, however this does not matter, only the
      // ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      // stepping further below works. So the values can be computed as below.
      //  Division through zero is prevented, even though technically that's not
      //  needed in C++ with IEEE 754 floating point values.
      double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

      double perpWallDist;

      // what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; // was there a wall hit?
      int side;    // was a NS or a EW wall hit?

      // calculate step and initial sideDist
      // ray fin ghadi w direction w bchhal ghnzido
      if (rayDirX < 0) // means to the left
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX; // mapX is the x coordinate of the map , posX is the x coordinate of the player
                                                // we do that to get the distance between the player and the next x side
      }
      else
      {
        stepX = 1;                                    // means to the right
        sideDistX = (mapX + 1.0 - posX) * deltaDistX; // we reverse the order of the subtraction because we want to get the distance
                                                      // between the player and the next x side
      }
      if (rayDirY < 0)
      {
        stepY = -1;                             // means to the bottom
        sideDistY = (posY - mapY) * deltaDistY; // same thing for the y coordinate , posY is larger than mapY
                                                // so we do the subtraction in the right order
      }
      else
      {
        stepY = 1; // means to the top
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      // perform DDA
      while (hit == 0)
      {
        // jump to next map square, either in x-direction, or in y-direction , we check if the distance to the next x side
        // is smaller than the distance to the next y side
        if (sideDistX < sideDistY) // if the distance to the next x side is smaller than the distance to the next y side
                                   // we move to the next x side map square
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        // Check if ray has hit a wall , if the map square is not represnted by a 0 then we hit a wall for sure
        if (worldMap[mapX][mapY] > 0)
          hit = 1;
      }
      // Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      // hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      // This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      // for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      // because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      // steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
      else
        perpWallDist = (sideDistY - deltaDistY);

      // Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      // calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if (drawStart < 0)
        drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if (drawEnd >= h)
        drawEnd = h - 1;

      // choose wall color
      ColorRGB color;
      switch (worldMap[mapX][mapY])
      {
      case 1:
        color = RGB_Red;
        break; // red
      case 2:
        color = RGB_Green;
        break; // green
      case 3:
        color = RGB_Blue;
        break; // blue
      case 4:
        color = RGB_White;
        break; // white
      default:
        color = RGB_Yellow;
        break; // yellow
      }

      // give x and y sides different brightness
      if (side == 1)
      {
        color = color / 2;
      }

      // draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
    }
    // timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; // frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime);                       // FPS counter
    redraw();
    cls();

    // speed modifiers
    double moveSpeed = frameTime * 5.0; // the constant value is in squares/second
    double rotSpeed = frameTime * 3.0;  // the constant value is in radians/second
    readKeys();
    // move forward if no wall in front of you
    if (keyDown(SDLK_UP))
    {
      if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
        posX += dirX * moveSpeed;
      if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
        posY += dirY * moveSpeed;
    }
    // move backwards if no wall behind you
    if (keyDown(SDLK_DOWN))
    {
      if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
        posX -= dirX * moveSpeed;
      if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
        posY -= dirY * moveSpeed;
    }
    // rotate to the right
    if (keyDown(SDLK_RIGHT))
    {
      // both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    // rotate to the left
    if (keyDown(SDLK_LEFT))
    {
      // both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
}
