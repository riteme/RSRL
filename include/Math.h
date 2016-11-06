//
// Copyright 2016 riteme
//

#ifndef RSRL_MATH_H_
#define RSRL_MATH_H_

#include <cstddef>

namespace rsr {

struct Vector4f {
    Vector4f();
    Vector4f(const float _x, const float _y, const float _z);
    Vector4f(const float _x, const float _y, const float _z, const float _w);

    float x;
    float y;
    float z;
    float w;

    /**
     * Vector addition
     */
    Vector4f operator+(const Vector4f &b) const;

    /**
     * Vector subtraction
     */
    Vector4f operator-(const Vector4f &b) const;

    /**
     * Scalar multiplication
     */
    Vector4f operator*(const float b) const;
    friend Vector4f operator*(const float b, const Vector4f &a);

    /**
     * Negative vector
     */
    Vector4f operator-() const;

    Vector4f &operator+=(const Vector4f &b);
    Vector4f &operator-=(const Vector4f &b);
    Vector4f &operator*=(const float b);

    float length() const;
};  // struct Vector4f

struct Matrix4f {
    Matrix4f();
    Matrix4f(const float m00, const float m01, const float m02, const float m03,
             const float m10, const float m11, const float m12, const float m13,
             const float m20, const float m21, const float m22, const float m23,
             const float m30, const float m31, const float m32,
             const float m33);

    /**
     * Elements access
     */
    float *operator[](const size_t x);
    const float *operator[](const size_t x) const;

    /**
     * Matrix addition
     */
    Matrix4f operator+(const Matrix4f &b) const;

    /**
     * Matrix subtraction
     */
    Matrix4f operator-(const Matrix4f &b) const;

    /**
     * Matrix multiplication
     */
    Matrix4f operator*(const Matrix4f &b) const;

    /**
     * Scalar multiplication
     */
    Matrix4f operator*(const float b) const;
    friend Matrix4f operator*(const float b, const Matrix4f &a);

    /**
     * Matrix-Vector multiplication
     */
    Vector4f operator*(const Vector4f &b) const;

    /**
     * Negative matrix
     */
    Matrix4f operator-() const;

    Matrix4f &operator+=(const Matrix4f &b);
    Matrix4f &operator-=(const Matrix4f &b);
    Matrix4f &operator*=(const Matrix4f &b);
    Matrix4f &operator*=(const float b);

 private:
    float _mat[4][4];
};  // struct Matrix4f

/**
 * Scale vector to 1 unit length
 * @param  vec target vector
 * @return     normalized vector
 */
Vector4f normalize(const Vector4f &vec);

/**
 * Vector cross production
 * @param  a vector a
 * @param  b vector b
 * @return   a cross b
 */
float cross(const Vector4f &a, const Vector4f &b);

/**
 * Vector dot production
 * @param  a vector a
 * @param  b vector b
 * @return   a dot b
 */
float dot(const Vector4f &a, const Vector4f &b);

Matrix4f identity();

Matrix4f transform(const float dx, const float dy, const float dz);
Matrix4f transform(const Vector4f &d);

Matrix4f scale(const float sx, const float sy, const float sz);
Matrix4f scale(const Vector4f s);

Matrix4f rotate_x(const float angle);
Matrix4f rotate_y(const float angle);
Matrix4f rotate_z(const float angle);

}  // namespace rsr

#endif  // RSRL_MATH_H_
