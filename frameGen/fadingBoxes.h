#include <SDL2/SDL.h>
#include <vector>

class FadingBoxes {
public:
  FadingBoxes(SDL_Renderer* rend) : renderer(rend), color({251,148,105,100}) {}
  // FIXME Rule of 3
  void draw(int x, int y);
private:
  SDL_Renderer* renderer;
  SDL_Color color;
  const int HEIGHT = 15;
  const int WIDTH = 46;
};
