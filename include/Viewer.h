//
// Copyright 2016 riteme
//

/**
 * Viewer tips:
 *     Press <F5> to take screenshot
 */

#ifndef RSRL_VIEWER_H_
#define RSRL_VIEWER_H_

#include "Texture.h"

#include <SDL2/SDL.h>

#include <atomic>
#include <thread>

namespace rsr {

class ViewWindow {
 public:
    ViewWindow(int width, int height);
    ~ViewWindow();

    /**
     * Update display
     * @param texture content
     */
    void update(const Texture& texture);

    /**
     * Process window events
     */
    void do_events();

    /**
     * Is window closed?
     * @return true for closed, false otherwise
     */
    bool is_closed() const;

    /**
     * Get window width
     * @return the width
     */
    int width() const;

    /**
     * Get window height
     * @return the height
     */
    int height() const;

 private:
    int _width;
    int _height;
    SDL_Window* _window;
    bool _closed;
};  // class ViewWindow

}  // namespace rsr

#endif  // RSRL_VIEWER_H_
