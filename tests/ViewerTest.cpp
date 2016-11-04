//
// Copyright 2016 riteme
//

#include "Viewer.h"
#include "Defs.h"

#include <SDL2/SDL_image.h>

using namespace rsr;

int main() {
    ViewWindow window(800, 600);

    SDL_Surface *backgound = nullptr;
    backgound = IMG_Load("window.png");
    ASSERTF(backgound, "Can't load `window.png`: %s", SDL_GetError());
    window.update(backgound);

    while (!window.is_closed()) {
        window.render();
    }

    SDL_FreeSurface(backgound);

    return 0;
}
