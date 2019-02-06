#include "fadingBoxes.h"

void FadingBoxes::draw(int x, int y) {
  std::vector<SDL_Rect> vec;
  vec.reserve(6);
  
  // Loop through the remaining boxes incrementally fading
  for (int i=0; i<6; i++) {
    vec[i] = {x, y-(i*HEIGHT), WIDTH, HEIGHT};
  }

  // Draw the 6 boxes
  for (int j=0; j<6; j++) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a - (j*10));
    SDL_RenderFillRect(renderer, &vec[j]);
  }
}

