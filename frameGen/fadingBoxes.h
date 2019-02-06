#include <SDL2/SDL.h>
#include <vector>

class FadingBoxes {
public:
  FadingBoxes(SDL_Renderer* rend) : renderer(rend) {}
  // FIXME Rule of 3
  void draw(int x, int y, int numOfBoxes);
private:
  SDL_Renderer* renderer;
  SDL_Color color = {251,148,105,120};
  const int HEIGHT = 8;
  const int WIDTH = 46;
};
