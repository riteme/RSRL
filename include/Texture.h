//
// Copyright 2016 riteme
//

#ifndef RSRL_TEXTURE_H_
#define RSRL_TEXTURE_H_

#include "Color.h"
#include "Defs.h"

#include <SDL2/SDL.h>

namespace rsr {

class Texture;

/**
 * Used for index color
 * Because SDL use y-first array
 * So keep pace with it for faster copying
 */
struct TextureIndexer {
    TextureIndexer(const size_t x, Texture *texture);

    Color4f &operator[](const size_t y);

 private:
    size_t _x;
    Texture *_texture;
};  // struct TextureIndexer

struct ConstTextureIndexer {
    ConstTextureIndexer(const size_t x, const Texture *texture);

    const Color4f &operator[](const size_t y) const;

 private:
    size_t _x;
    const Texture *_texture;
};  // struct ConstTextureIndexer

class Texture {
 public:
    friend struct TextureIndexer;
    friend struct ConstTextureIndexer;

    Texture(const int width, const int height);
    Texture(const Texture &b);
    Texture(Texture &&b);
    ~Texture();

    Texture &operator=(const Texture &b);
    Texture &operator=(Texture &&b);

    TextureIndexer operator[](const size_t x);
    const ConstTextureIndexer operator[](const size_t x) const;

    /**
     * Clear the texture with a specified color
     * @param c color
     */
    void clear(const Color4f &c);

    /**
     * Read texture data to a SDL_Surface
     * @param dest the surface
     */
    void read_data(SDL_Surface *&dest) const;

    /**
     * Get texture width
     * @return the width
     */
    int width() const;

    /**
     * Get texture height
     * @return the height
     */
    int height() const;

    /**
     * Sample color by u-v coordination
     * @param  u u axis (horizontal)
     * @param  v v axis (vertical)
     * @return   color
     * #remark:
     *     Start from left-top corner
     */
    Color4f map(const float u, const float v) const;

 private:
    Color4f sample(const float x, const float y, const float x1, const float y1,
                   const float x2, const float y2, const float x3,
                   const float y3, const float x4, const float y4) const;

    int _width;
    int _height;
    Color4f *_data;
};  // class Texture

}  // namespace rsr

#endif  // RSRL_TEXTURE_H_
