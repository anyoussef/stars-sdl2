#include "defs.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static bool app_running = 1;

typedef struct {
  int x;
  int y;
  int life;
  Uint32 color;
} Star;

Star stars[MAX_STARS];

int rand_range(int min, int max) { return min + rand() % (max - min); }

Uint32 random_star_color() {

  int choice = rand() % 7;

  switch (choice) {
  case 0:
    return WHITE;
  case 1:
    return OFF_WHITE;
  case 2:
    return GRAY;
  case 3:
    return BLACK;
  case 4:
    return BLUE;
  case 5:
    return YELLOW;
  case 6:
    return PURPLE;
  default:
    return WHITE;
  }
}

void draw_border(SDL_Surface *psurface, Uint32 color) {

  SDL_Rect rect = {0, 0, 3, 3};

  // top
  for (int x = BORDER_OFFSET; x < WIDTH - BORDER_OFFSET; x++) {
    rect.x = x;
    rect.y = BORDER_OFFSET;
    SDL_FillRect(psurface, &rect, color);
  }

  // bottom
  for (int x = BORDER_OFFSET; x < WIDTH - BORDER_OFFSET; x++) {
    rect.x = x;
    rect.y = HEIGHT - BORDER_OFFSET;
    SDL_FillRect(psurface, &rect, color);
  }

  // left
  for (int y = BORDER_OFFSET; y < HEIGHT - BORDER_OFFSET; y++) {
    rect.x = BORDER_OFFSET;
    rect.y = y;
    SDL_FillRect(psurface, &rect, color);
  }

  // right
  for (int y = BORDER_OFFSET; y < HEIGHT - BORDER_OFFSET; y++) {
    rect.x = WIDTH - BORDER_OFFSET;
    rect.y = y;
    SDL_FillRect(psurface, &rect, color);
  }
}

void draw_star(SDL_Surface *surface, int x, int y, Uint32 color) {

  SDL_Rect rect = {x, y, 3, 3};

  // left
  SDL_Rect rect1 = {x - 1, y + 1, 1, 1};

  // right
  SDL_Rect rect2 = {x + 3, y + 1, 1, 1};

  // top
  SDL_Rect rect3 = {x + 1, y - 1, 1, 1};

  // bottom
  SDL_Rect rect4 = {x + 1, y + 3, 1, 1};

  SDL_FillRect(surface, &rect, color);
  SDL_FillRect(surface, &rect1, color);
  SDL_FillRect(surface, &rect2, color);
  SDL_FillRect(surface, &rect3, color);
  SDL_FillRect(surface, &rect4, color);
}

void init_stars() {
  for (int i = 0; i < MAX_STARS; i++) {
    stars[i].x = rand_range(STAR_MIN_X, STAR_MAX_X);
    stars[i].y = rand_range(STAR_MIN_Y, STAR_MAX_Y);
    stars[i].life = rand() % 200;
    stars[i].color = random_star_color();
  }
}

void update_stars(SDL_Surface *surface) {

  for (int i = 0; i < MAX_STARS; i++) {

    if (stars[i].life <= 0) {
      stars[i].x = rand_range(STAR_MIN_X, STAR_MAX_X);
      stars[i].y = rand_range(STAR_MIN_Y, STAR_MAX_Y);
      stars[i].life = rand() % 200;
      stars[i].color = random_star_color();
    }

    draw_star(surface, stars[i].x, stars[i].y, stars[i].color);
    stars[i].life--;
  }
}

int main(int argc, char *argv[]) {

  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Failure - Init Failed\n");
    return -1;
  }

  SDL_Window *pwindow =
      SDL_CreateWindow("Stars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED);

  if (!pwindow) {
    printf("Window creation failed\n");
    return -1;
  }

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
  init_stars();

  while (app_running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_QUIT) {
        app_running = 0;
        printf("Quitting...\n");
      }
    }

    SDL_FillRect(psurface, NULL, BLACK);
    update_stars(psurface);
    draw_border(psurface, GRAY);
    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(FPS_DELAY);
  }

  SDL_DestroyWindow(pwindow);
  SDL_Quit();

  return 0;
}
