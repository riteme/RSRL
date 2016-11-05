//
// Copyright 2016 riteme
//

#include "Viewer.h"
#include "Defs.h"

#include <ctime>

#include <string>

namespace rsr {

static int viewer_count = 0;

ViewWindow::ViewWindow(int width, int height)
    : _width(width), _height(height), _window(nullptr), _closed(false) {
    ASSERT(viewer_count == 0, "Can't open 2 viewer at one time");
    viewer_count++;

    ASSERTF(SDL_Init(SDL_INIT_VIDEO) == 0, "Can't initialize SDL2: %s",
            SDL_GetError());

    _window = SDL_CreateWindow("RSRL Viewer", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, 0);
    ASSERTF(_window, "Can't create window: %s", SDL_GetError());
}

ViewWindow::~ViewWindow() {
    viewer_count--;

    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void ViewWindow::update(const Texture& texture) {
    ASSERT(!_closed, "Window closed");

    SDL_Surface* dest = SDL_GetWindowSurface(_window);
    ASSERT(dest, "Can't get window's surface");

    texture.read_data(dest);

    SDL_UpdateWindowSurface(_window);
}

void ViewWindow::do_events() {
    ASSERT(!_closed, "Window closed");

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            _closed = true;
        else if (event.type == SDL_KEYDOWN)
            if (event.key.keysym.sym == SDLK_F5)
                SDL_SaveBMP(SDL_GetWindowSurface(_window),
                            (std::string("screenshot") +
                             std::to_string(time(nullptr)) + ".bmp")
                                .data());
    }
}

bool ViewWindow::is_closed() const {
    return _closed;
}

int ViewWindow::width() const {
    return _width;
}

int ViewWindow::height() const {
    return _height;
}

}  // namespace rsr
