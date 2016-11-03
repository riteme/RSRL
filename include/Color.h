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

    Color operator+(const Color &b) const;
    Color operator*(const float r) const;
    Color operator-() const;

    Color &operator+=(const Color &b);
    Color &operator*=(const float r);
};

#endif
