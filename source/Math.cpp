//
// Copyright 2016 riteme
//

#ifndef RSRL_MATH_H_
#define RSRL_MATH_H_

#include "Defs.h"
#include "Math.h"

#include <cstring>

Vector::Vector()
    : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Vector::Vector(const float _x, const float _y, const float _z)
    : x(_x), y(_y), z(_z), w(1.0f) {}

Vector::Vector(const float _x, const float _y, const float _z, const float _w)
    : x(_x), y(_y), z(_z), w(_w) {}

Vector Vector::operator+(const Vector &b) const {
    return Vector(x + b.x, y + b.y, z + b.z);
}

Vector Vector::operator-(const Vector &b) const {
    return Vector(x - b.x, y - b.y, z - b.z);
}

Vector Vector::operator*(const float b) const {
    return Vector(x * b, y * b, z * b);
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}

Vector &operator+=(const Vector &b) {
    *this = *this + b;

    return *this;
}

Vector &operator-=(const Vector &b) {
    *this = *this - b;

    return *this;
}

Vector &operator*=(const float b) {
    *this = *this * b;

    return *this;
}

Matrix() {
    memset(_mat, 0, sizeof(_mat));
    _mat[0][0] = _mat[1][1] = _mat[2][2] = _mat[3][3] = 1.0f;
}

Matrix(const float m00, const float m01, const float m02, const float m03,
       const float m10, const float m11, const float m12, const float m13,
       const float m20, const float m21, const float m22, const float m23,
       const float m30, const float m31, const float m32, const float m33);

Matrix operator+(const Matrix &b) const;
Matrix operator-(const Matrix &b) const;
Matrix operator*(const Matrix &b) const;
Matrix operator*(const float b) const;
Vector operator*(const Vector &b) const;
Matrix operator-() const;
friend Matrix operator*(const float b, const Matrix &a);

Matrix &operator+=(const Matrix &b);
Matrix &operator-=(const Matrix &b);
Matrix &operator*=(const Matrix &b);
Matrix &operator*=(const float b);

#endif
