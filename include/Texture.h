//
// Copyright 2016 riteme
//

#ifndef RSRL_TEXTURE_H_
#define RSRL_TEXTURE_H_

#include "Color.h"
#include "Defs.h"

#include <SDL2/SDL.h>

namespace rsr {

class Texture {
 public:
    Texture(const int width, const int height);
    Texture(const Texture &b);
    Texture(Texture &&b);
    ~Texture();

    Texture &operator=(const Texture &b);
    Texture &operator=(Texture &&b);

    Color *operator[](const size_t x);
    const Color *operator[](const size_t x) const;

    void clear(const Color &c);
    void read_data(SDL_Surface *&dest);

    int width() const;
    int height() const;
    Color map(const float u, const float v) const;

 private:
    Color sample(const float x, const float y, const float x1, const float y1,
                 const float x2, const float y2, const float x3, const float y3,
                 const float x4, const float y4) const;

    int _width;
    int _height;
    Color *_data;
};  // class Texture

}  // namespace rsr

#endif  // RSRL_TEXTURE_H_
