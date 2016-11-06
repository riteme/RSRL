//
// Copyright 2016 riteme
//

#include "Renderer.h"

#include <algorithm>

namespace rsr {

Renderer::Renderer(Texture *texture) : _target(texture) {}

void Renderer::set_target(Texture *texture) {
    _target = texture;
}

void Renderer::clear(const Color4f &c) {
    _target->clear(c);
}

void Renderer::draw_pixel(const int x, const int y, const Color4f &c) {
    if (0 <= x && x < _target->width() && 0 <= y && y < _target->height())
        (*_target)[x][y] = c;
}

void Renderer::draw_line(const int x1, const int y1, const int x2, const int y2,
                         const Color4f &c) {
    if (x1 == x2 && y1 == y2)
        draw_pixel(x1, y1, c);
    else if (x1 == x2)
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
            draw_pixel(x1, y, c);
    else if (y1 == y2)
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
            draw_pixel(x, y1, c);
    else {
        // Bresenham Algorithm (float version)

        int _x1 = x1, _y1 = y1, _x2 = x2, _y2 = y2;

        if (_x1 > _x2) {
            std::swap(_x1, _x2);
            std::swap(_y1, _y2);
        }

        float delta_x = _x1 - _x2;
        float delta_y = _y1 - _y2;
        float k = delta_y / delta_x;
        float e = 0.0f;

        int y = _y1;
        int dy = k > 0 ? 1 : -1;
        k = fabs(k);

        for (int x = _x1; x < _x2; x++) {
            if (e < 0)
                draw_pixel(x, y, c);
            else {
                while (e >= 0) {
                    e -= 1.0f;
                    draw_pixel(x, y, c);
                    y += dy;
                }  // while
            }

            e += k;
        }

        while (y != _y2) {
            draw_pixel(_x2, y, c);
            y += dy;
        }  // while
        draw_pixel(_x2, _y2, c);
    }
}

void Renderer::apply() {}

}  // namespace rsr
