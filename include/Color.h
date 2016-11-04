//
// Copyright 2016 riteme
//

#ifndef RSRL_COLOR_H_
#define RSRL_COLOR_H_

struct Color {
    Color();
    Color(const float _red, const float _green, const float _blue);
    Color(const float _red, const float _green, const float _blue,
          const float _alpha);

    float red;
    float green;
    float blue;
    float alpha;

    /**
     * Blend b to this by alpha
     */
    Color operator+(const Color &b) const;

    /**
     * Scale color
     */
    Color operator*(const float r) const;

    /**
     * Negative color
     */
    Color operator-() const;

    Color &operator+=(const Color &b);
    Color &operator*=(const float r);
};  // struct Color

#endif  // RSRL_COLOR_H_
