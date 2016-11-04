//
// Copyright 2016 riteme
//

#include "Viewer.h"
#include "Defs.h"

static int viewer_count = 0;

ViewWindow::ViewWindow(int width, int height)
        : _width(width)
        , _height(height)
        , _window(nullptr)
        , _renderer(nullptr)
        , _texture(nullptr)
        , _closed(false) {
    ASSERT(viewer_count == 0, "Can't open 2 viewer at one time");
    viewer_count++;

    ASSERTF(SDL_Init(SDL_INIT_VIDEO) == 0, "Can't initialize SDL2: %s",
            SDL_GetError());

    _window = SDL_CreateWindow("RSRL Viewer", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height,
                               SDL_WINDOW_SHOWN);
    ASSERTF(_window, "Can't create window: %s", SDL_GetError());

    _renderer = SDL_CreateRenderer(
        _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ASSERTF(_renderer, "Can't create renderer: %s", SDL_GetError());
}

ViewWindow::~ViewWindow() {
    viewer_count--;

    if (_texture)
        SDL_DestroyTexture(_texture);

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void ViewWindow::update(SDL_Surface *surface) {
    ASSERT(surface->w == _width, "Update display failed: Incorrect width");
    ASSERT(surface->h == _height, "Update display failed: Incorrect height");

    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    _texture = SDL_CreateTexture(_renderer, surface->format->format,
                                 SDL_TEXTUREACCESS_STATIC, _width, _height);
    ASSERTF(_texture, "Can't create texture: %s", SDL_GetError());
}

void ViewWindow::render() {
    ASSERT(!_closed, "Window closed");

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    if (_texture)
        SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);

    SDL_RenderPresent(_renderer);

    // Process window events
    SDL_Event event;
    while (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT)
            _closed = true;
}

bool ViewWindow::is_closed() const {
    return _closed;
}
