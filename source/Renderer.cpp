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
        // Bresenham Algorithm (integer version)
        int dy, y;
        if (x1 < x2) {
            dy = y1 < y2 ? 1 : -1;
            y = y1;
        } else {
            dy = y1 > y2 ? 1 : -1;
            y = y2;
        }

        int delta_x = std::abs(x1 - x2);
        int delta_y = std::abs(y1 - y2);
        int e = 0;
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            if (e < 0)
                draw_pixel(x, y, c);
            else {
                while (e >= 0) {
                    e -= delta_x;
                    draw_pixel(x, y, c);
                    y += dy;
                }  // while
            }

            e += delta_y;
        }
    }
}

void Renderer::draw_triangle(const int x1, const int y1, const int x2,
                             const int y2, const int x3, const int y3,
                             const Color4f &c) {}

void Renderer::_draw_right_triangle(const int y1, const int y2, const int lx,
                                    const int rx, const int ry,
                                    const Color4f &c) {
    if (rx < lx)
        return;
    if (rx == lx)
        draw_line(lx, y1, lx, y2, c);
    else {
        float _ty = std::min(y1, y2), _by = std::max(y1, y2);

        float k1 = static_cast<float>(_ty - ry) / static_cast<float>(lx - rx);
        float k2 = static_cast<float>(_by - ry) / static_cast<float>(lx - rx);

        for (int x = lx; x <= rx; x++) {
            draw_line(x, _ty + 0.5f, x, _by + 0.5f, c);

            _ty += k1;
            _by += k2;
        }  // for
    }
}

void Renderer::_draw_left_triangle(const int y1, const int y2, const int rx,
                                   const int lx, const int ly,
                                   const Color4f &c) {
    if (rx < lx)
        return;
    if (rx == lx)
        draw_line(lx, y1, lx, y2, c);
    else {
        float _ty = std::min(y1, y2), _by = std::max(y1, y2);

        float k1 = static_cast<float>(_ty - ly) / static_cast<float>(rx - lx);
        float k2 = static_cast<float>(_by - ly) / static_cast<float>(rx - lx);

        for (int x = rx; x >= lx; x--) {
            draw_line(x, _ty + 0.5f, x, _by + 0.5f, c);

            _ty -= k1;
            _by -= k2;
        }  // for
    }
}

void Renderer::apply() {}

}  // namespace rsr
