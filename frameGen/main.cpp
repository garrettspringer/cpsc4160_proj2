#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"

const std::string TITLE = "Garrett's Electrophoresis";
const std::string NAME = "ghsprin"; // username for prefix of image file

const int WIDTH = 734;
const int HEIGHT = 460;

// Draws concentric circles overlapping eachother
void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) 
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) 
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
    }
}

// Writes your title at the bottom left of the image
void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/saved_by_zero.ttf", 22);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0xff, 255, 200, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

int main(void) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      std::cout << "Failed to initialize SDL2" << std::endl;
      return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );
    // Apparently we can't use hardware acceleration with
    // SDL_GetWindowSurface
    SDL_Renderer* renderer = SDL_CreateRenderer( 
      window, -1, SDL_RENDERER_SOFTWARE
    );

    // First set the blend mode so that alpha blending will work;
    // the default blend mode is SDL_BLENDMODE_NONE!
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );

    // Draws the pink background
    SDL_SetRenderDrawColor(renderer, 119, 0, 176, 255);
    SDL_RenderClear(renderer);

    // Draws the red circle
    /*SDL_Point center = {320, 240};
    SDL_Color red = {255,0,0,255};
    drawCircle(renderer, center, 50, red);*/

    // Draws the gel rectangles
    // Sets the light pink color of large rectangles
    SDL_SetRenderDrawColor(renderer, 140, 18, 165, 100);
    // Large rectangle dimensions
    SDL_Rect large_rect;
    large_rect.x = 14;
    large_rect.y = 0;
    large_rect.w = 52;
    large_rect.h = 460;

    // Render rect
    SDL_RenderFillRect(renderer, &large_rect);

    // Writes name in bottom left corner
    writeName(renderer);
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    // Game loop
    // Keeps looping until esc is pressed
    SDL_Event event;
    const Uint8* keystate;
    while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
      }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  }
  catch (const std::string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return EXIT_SUCCESS;
}
