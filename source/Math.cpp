//
// Copyright 2016 riteme
//

#include "Math.h"
#include "Defs.h"

#include <cmath>
#include <cstddef>
#include <cstring>

Vector::Vector() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

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

Vector operator*(const float b, const Vector &a) {
    return a * b;
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}

Vector &Vector::operator+=(const Vector &b) {
    *this = *this + b;

    return *this;
}

Vector &Vector::operator-=(const Vector &b) {
    *this = *this - b;

    return *this;
}

Vector &Vector::operator*=(const float b) {
    *this = *this * b;

    return *this;
}

float Vector::length() const {
    return sqrt(x * x + y * y + z * z);
}

Matrix::Matrix() {
    memset(_mat, 0, sizeof(_mat));
}

Matrix::Matrix(const float m00, const float m01, const float m02,
               const float m03, const float m10, const float m11,
               const float m12, const float m13, const float m20,
               const float m21, const float m22, const float m23,
               const float m30, const float m31, const float m32,
               const float m33) {
    _mat[0][0] = m00;
    _mat[0][1] = m01;
    _mat[0][2] = m02;
    _mat[0][3] = m03;
    _mat[1][0] = m10;
    _mat[1][1] = m11;
    _mat[1][2] = m12;
    _mat[1][3] = m13;
    _mat[2][0] = m20;
    _mat[2][1] = m21;
    _mat[2][2] = m22;
    _mat[2][3] = m23;
    _mat[3][0] = m30;
    _mat[3][1] = m31;
    _mat[3][2] = m32;
    _mat[3][3] = m33;
}

float *Matrix::operator[](const size_t x) {
    ASSERTF(x < 4, "Invalid argument x: expected in [0, 3], got %zu.", x);

    return &_mat[x][0];
}

const float *Matrix::operator[](const size_t x) const {
    ASSERTF(x < 4, "Invalid argument x: expected in [0, 3], got %zu.", x);

    return &_mat[x][0];
}

Matrix Matrix::operator+(const Matrix &b) const {
    Matrix c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] + b[i][j];

    return c;
}

Matrix Matrix::operator-(const Matrix &b) const {
    Matrix c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] - b[i][j];

    return c;
}

Matrix Matrix::operator*(const Matrix &b) const {
    Matrix c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            for (size_t k = 0; k < 4; k++)
                c[i][j] += _mat[i][k] * b[k][j];

    return c;
}

Matrix Matrix::operator*(const float b) const {
    Matrix c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = _mat[i][j] * b;

    return c;
}

Vector Matrix::operator*(const Vector &b) const {
    return Vector(b.x * _mat[0][0] + b.y * _mat[1][0] + b.z * _mat[2][0] +
                      b.w * _mat[3][0],
                  b.x * _mat[0][1] + b.y * _mat[1][1] + b.z * _mat[2][1] +
                      b.w * _mat[3][1],
                  b.x * _mat[0][2] + b.y * _mat[1][2] + b.z * _mat[2][2] +
                      b.w * _mat[3][2],
                  b.x * _mat[0][3] + b.y * _mat[1][3] + b.z * _mat[2][3] +
                      b.w * _mat[3][3]);
}

Matrix Matrix::operator-() const {
    Matrix c;
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            c[i][j] = -_mat[i][j];

    return c;
}

Matrix operator*(const float b, const Matrix &a) {
    return a * b;
}

Matrix &Matrix::operator+=(const Matrix &b) {
    *this = *this + b;

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &b) {
    *this = *this - b;

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &b) {
    *this = *this * b;

    return *this;
}

Matrix &Matrix::operator*=(const float b) {
    *this = *this * b;

    return *this;
}

void Matrix::load_identity() {
    memset(_mat, 0, sizeof(_mat));
    _mat[0][0] = _mat[1][1] = _mat[2][2] = _mat[3][3] = 1.0f;
}

Vector normalize(const Vector &vec) {
    return vec * (1.0f / vec.length());
}
