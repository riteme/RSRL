//
// Copyright 2016 riteme
//

#include "Texture.h"
#include "Defs.h"

#include <cmath>
#include <cstring>

namespace rsr {

TextureIndexer::TextureIndexer(const size_t x, Texture *texture)
    : _x(x), _texture(texture) {}

Color &TextureIndexer::operator[](const size_t y) {
    return _texture->_data[y * _texture->width() + _x];
}

ConstTextureIndexer::ConstTextureIndexer(const size_t x, const Texture *texture)
    : _x(x), _texture(texture) {}

const Color &ConstTextureIndexer::operator[](const size_t y) const {
    return _texture->_data[y * _texture->width() + _x];
}

Texture::Texture(const int width, const int height)
    : _width(width), _height(height) {
    _data = new Color[width * height];
}

Texture::Texture(const Texture &b) {
    _width = b.width();
    _height = b.height();
    memcpy(_data, b._data, sizeof(Color) * width() * height());
}

Texture::Texture(Texture &&b) {
    if (_data)
        delete[] _data;

    _width = b.width();
    _height = b.height();
    _data = b._data;
    b._data = nullptr;
}

Texture::~Texture() {
    if (_data)
        delete[] _data;
}

Texture &Texture::operator=(const Texture &b) {
    if (_data)
        delete[] _data;

    _width = b.width();
    _height = b.height();
    _data = new Color[width() * height()];
    memcpy(_data, b._data, sizeof(Color) * width() * height());

    return *this;
}

Texture &Texture::operator=(Texture &&b) {
    if (_data)
        delete[] _data;

    _width = b.width();
    _height = b.height();
    _data = b._data;
    b._data = nullptr;

    return *this;
}

TextureIndexer Texture::operator[](const size_t x) {
    return TextureIndexer(x, this);
}

const ConstTextureIndexer Texture::operator[](const size_t x) const {
    return ConstTextureIndexer(x, this);
}

void Texture::clear(const Color &c) {
    Color *ptr = _data;
    Color *end = _data + width() * height();
    for (; ptr != end; ptr++)
        *ptr = c;
}

void Texture::read_data(SDL_Surface *&dest) const {
    ASSERT(dest, "Invalid argument 'dest': NULL Surface");
    ASSERT(width() <= dest->w, "Incompatible width");
    ASSERT(height() <= dest->h, "Incompatible height");

    if (SDL_MUSTLOCK(dest))
        SDL_LockSurface(dest);

    SDL_Color *data = reinterpret_cast<SDL_Color *>(dest->pixels);
    ASSERTF(sizeof(SDL_Color) == 4, "SDL_Color padded: current is %zu bytes",
            sizeof(SDL_Color));

    Color *csrc = _data;
    Color *end = _data + width() * height();
    SDL_Color *cdest = data;
    while (csrc != end) {
        cdest->r = csrc->red * 255.0f;
        cdest->g = csrc->green * 255.0f;
        cdest->b = csrc->blue * 255.0f;

        csrc++;
        cdest++;
    }  // while

    if (SDL_MUSTLOCK(dest))
        SDL_UnlockSurface(dest);
}

int Texture::width() const {
    return _width;
}

int Texture::height() const {
    return _height;
}

Color Texture::map(const float u, const float v) const {
    ASSERTF(0.0 <= u && u <= 1.0,
            "Invalid argument 'u': expected in [0.0, 1.0], got %.06f", u);
    ASSERTF(0.0 <= v && v <= 1.0,
            "Invalid argument 'v': expected in [0.0, 1.0], got %.06f", v);

    float x = width() * u;
    float y = height() * v;
    float px = floorf(x);
    float py = floorf(y);
    float dx = x - px;
    float dy = y - py;

    if (dx <= 0.5 && dy <= 0.5)
        return sample(x, y, px, py, px - 1, py, px, py - 1, px - 1, py - 1);
    else if (dx <= 0.5 && dy > 0.5)
        return sample(x, y, px, py, px - 1, py, px, py + 1, px - 1, py + 1);
    else if (dx > 0.5 && dy <= 0.5)
        return sample(x, y, px, py, px + 1, py, px, py - 1, px + 1, py - 1);
    else
        return sample(x, y, px, py, px + 1, py, px, py + 1, px + 1, py + 1);
}

Color Texture::sample(const float x, const float y, const float x1,
                      const float y1, const float x2, const float y2,
                      const float x3, const float y3, const float x4,
                      const float y4) const {
    float nx = INFINITY, ny = INFINITY;

    if (0 <= x1 && x1 <= width() && 0 <= y1 && y1 <= height() &&
        powf(x1 - x, 2.0f) + powf(y1 - x, 2.0f) <
            powf(nx - x, 2.0f) + powf(ny - x, 2.0f)) {
        nx = x1;
        ny = y1;
    }

    if (0 <= x2 && x2 <= width() && 0 <= y2 && y2 <= height() &&
        powf(x2 - x, 2.0f) + powf(y2 - x, 2.0f) <
            powf(nx - x, 2.0f) + powf(ny - x, 2.0f)) {
        nx = x2;
        ny = y2;
    }

    if (0 <= x3 && x3 <= width() && 0 <= y3 && y3 <= height() &&
        powf(x3 - x, 2.0f) + powf(y3 - x, 2.0f) <
            powf(nx - x, 2.0f) + powf(ny - x, 2.0f)) {
        nx = x3;
        ny = y3;
    }

    if (0 <= x4 && x4 <= width() && 0 <= y4 && y4 <= height() &&
        powf(x4 - x, 2.0f) + powf(y4 - x, 2.0f) <
            powf(nx - x, 2.0f) + powf(ny - x, 2.0f)) {
        nx = x4;
        ny = y4;
    }

    return (*this)[static_cast<size_t>(nx)][static_cast<size_t>(ny)];
}

}  // namespace rsr
