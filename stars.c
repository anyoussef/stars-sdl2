#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEIGHT 900
#define WIDTH 900
#define TEXTURE 20

#define WHITE 0xffffffff
#define OFF_WHITE 0xfaf9f6ff
#define GRAY 0xff808080

static bool app_running = 1;

void draw_border(SDL_Window *pwindow, SDL_Surface *psurface, Uint32 color) {

  SDL_Rect rect = {0, 0, 3, 3};

  // top
  for (int x = 10; x < WIDTH - 10; x++) {
    rect.x = x;
    rect.y = 10;
    SDL_FillRect(psurface, &rect, color);
  }

  // bottom
  for (int x = 10; x < WIDTH - 10; x++) {
    rect.x = x;
    rect.y = HEIGHT - 10;
    SDL_FillRect(psurface, &rect, color);
  }

  // left
  for (int y = 10; y < HEIGHT - 10; y++) {
    rect.x = 10;
    rect.y = y;
    SDL_FillRect(psurface, &rect, color);
  }

  // right
  for (int y = 10; y < HEIGHT - 10; y++) {
    rect.x = WIDTH - 10;
    rect.y = y;
    SDL_FillRect(psurface, &rect, color);
  }

  SDL_UpdateWindowSurface(pwindow);
}

int main(void) {

  int success = SDL_Init(SDL_INIT_VIDEO);

  if (success != 0) {
    printf("Failure - Init Failed");
    exit(-1);
  }

  SDL_Window *pwindow =
      SDL_CreateWindow("raycast", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  while (app_running) {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        app_running = 0;
        printf("Quitting...\n");
        break;
      }
    }

    draw_border(pwindow, psurface, GRAY);
  }

  return 0;
}
