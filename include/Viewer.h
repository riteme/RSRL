//
// Copyright 2016 riteme
//

/**
 * Viewer tips:
 *     Press <F5> to take screenshot
 */

#ifndef RSRL_VIEWER_H_
#define RSRL_VIEWER_H_

#include <SDL2/SDL.h>

#include <atomic>
#include <thread>

class ViewWindow {
 public:
    ViewWindow(int width, int height);
    ~ViewWindow();

    /**
     * Update display
     * @param surface content
     */
    void update(SDL_Surface* surface);

    /**
     * Render to screen
     */
    void render();

    /**
     * Is window closed?
     * @return true for closed, false otherwise
     */
    bool is_closed() const;

 private:
    int           _width;
    int           _height;
    SDL_Window*   _window;
    SDL_Renderer* _renderer;
    SDL_Texture*  _texture;
    bool          _closed;
};  // class ViewWindow

#endif  // RSRL_VIEWER_H_
