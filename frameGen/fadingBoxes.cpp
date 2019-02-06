#include "fadingBoxes.h"

void FadingBoxes::draw(int x, int y) {
  std::vector<SDL_Rect> vec;
  vec.reserve(8);
  
  // Loop through the remaining boxes incrementally fading
  for (int i=0; i<8; i++) {
    vec[i] = {x, y-(i*HEIGHT), WIDTH, HEIGHT};
  }

  // Draw the 10 boxes
  for (int j=0; j<8; j++) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a - (j*10));
    SDL_RenderFillRect(renderer, &vec[j]);
  }
}

