//
// Copyright 2016 riteme
//

#include "Color.h"
#include "Defs.h"

namespace rsr {

Color::Color() : red(0.0), green(0.0), blue(0.0), alpha(1.0) {}

Color::Color(const float _red, const float _green, const float _blue)
    : red(_red), green(_green), blue(_blue), alpha(1.0) {}

Color::Color(const float _red, const float _green, const float _blue,
             const float _alpha)
    : red(_red), green(_green), blue(_blue), alpha(_alpha) {}

Color Color::operator+(const Color &b) const {
    return Color(b.red * b.alpha + red * alpha * (1.0f - b.alpha),
                 b.green * b.alpha + green * alpha * (1.0f - b.alpha),
                 b.blue * b.alpha + blue * alpha * (1.0f - b.alpha),
                 1.0f - (1.0f - alpha) * (1.0f - b.alpha));
}

Color Color::operator*(const float r) const {
    ASSERTF(0.0f <= r && r <= 1.0f,
            "Invalid argument 'r': expected in [0.0, 1.0], got %.6f.", r);

    return Color(red * r, green * r, blue * r, alpha);
}

Color Color::operator-() const {
    return Color(1.0f - red, 1.0f - green, 1.0f - blue, alpha);
}

Color &Color::operator+=(const Color &b) {
    *this = *this + b;

    return *this;
}

Color &Color::operator*=(const float r) {
    *this = *this * r;

    return *this;
}

void Color::correct() {
    if (red < 0.0f)
        red = 0.0f;
    else if (red > 1.0f)
        red = 1.0f;

    if (green < 0.0f)
        green = 0.0f;
    else if (green > 1.0f)
        green = 1.0f;

    if (blue < 0.0f)
        blue = 0.0f;
    else if (blue > 1.0f)
        blue = 1.0f;

    if (alpha < 0.0f)
        alpha = 0.0f;
    else if (alpha > 1.0f)
        alpha = 1.0f;
}

}  // namespace rsr
