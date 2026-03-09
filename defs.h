#ifndef STARS_H
#define STARS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEIGHT 1080
#define WIDTH 1800

#define WHITE 0xFFFFFFFF
#define OFF_WHITE 0xFFFAF9F6
#define GRAY 0xFF808080
#define BLACK 0xFF000000
#define BLUE 0xFF86C5D8
#define YELLOW 0xFFF1E86E
#define PURPLE 0xFFB194D1

#define FPS_DELAY 50
#define MAX_STARS 600

#define BORDER_OFFSET 10
#define BORDER_THICKNESS 3

#define STAR_MIN_X (BORDER_OFFSET + BORDER_THICKNESS)
#define STAR_MAX_X (WIDTH - BORDER_OFFSET - BORDER_THICKNESS)

#define STAR_MIN_Y (BORDER_OFFSET + BORDER_THICKNESS)
#define STAR_MAX_Y (HEIGHT - BORDER_OFFSET - BORDER_THICKNESS)

typedef struct {
  int x;
  int y;
  int life;
  Uint32 color;
} Star;

int rand_range(int min, int max);
Uint32 random_star_color();
void draw_border(SDL_Surface *psurface, Uint32 color);
void draw_star(SDL_Surface *surface, int x, int y, Uint32 color);
void init_stars();
void update_stars(SDL_Surface *surface);

#endif
