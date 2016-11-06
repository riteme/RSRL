//
// Copyright 2016 riteme
//

#ifndef RSRL_RENDERER_H_
#define RSRL_RENDERER_H_

#include "Defs.h"
#include "Math.h"
#include "Texture.h"

namespace rsr {

class Renderer {
 public:
    Renderer(Texture *texture);

    void set_target(Texture *texture);

    void clear(const Color4f &c);
    void draw_pixel(const int x, const int y, const Color4f &c);
    void draw_line(const int x1, const int y1, const int x2, const int y2,
                   const Color4f &c);
    void apply();

 private:
    Texture *_target;
};  // class Renderer

}  // namespace rsr

#endif  // RSRL_RENDERER_H_
