#include "fadingBoxes.h"

void FadingBoxes::draw(int x, int y, int numOfBoxes) {
  std::vector<SDL_Rect> vec;
  vec.reserve(numOfBoxes);
  
  // Loop through the remaining boxes incrementally fading
  for (int i=0; i<numOfBoxes; i++) {
    vec[i] = {x, y-(i*HEIGHT), WIDTH, HEIGHT};
  }

  // Draw the boxes
  for (int j=0; j<numOfBoxes; j++) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a - (j*10));
    SDL_RenderFillRect(renderer, &vec[j]);
  }
}

