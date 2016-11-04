//
// Copyright 2016 riteme
//

#ifndef RSRL_MATH_H_
#define RSRL_MATH_H_

#include <cstddef>

struct Vector {
    Vector();
    Vector(const float _x, const float _y, const float _z);
    Vector(const float _x, const float _y, const float _z, const float _w);

    float x;
    float y;
    float z;
    float w;

    /**
     * Vector addition
     */
    Vector operator+(const Vector &b) const;

    /**
     * Vector subtraction
     */
    Vector operator-(const Vector &b) const;

    /**
     * Scalar multiplication
     */
    Vector operator*(const float b) const;
    friend Vector operator*(const float b, const Vector &a);

    /**
     * Negative vector
     */
    Vector operator-() const;

    Vector &operator+=(const Vector &b);
    Vector &operator-=(const Vector &b);
    Vector &operator*=(const float b);

    float length() const;
};  // struct Vector

struct Matrix {
    Matrix();
    Matrix(const float m00, const float m01, const float m02, const float m03,
           const float m10, const float m11, const float m12, const float m13,
           const float m20, const float m21, const float m22, const float m23,
           const float m30, const float m31, const float m32, const float m33);

    /**
     * Elements access
     */
    float *operator[](const size_t x);
    const float *operator[](const size_t x) const;

    /**
     * Matrix addition
     */
    Matrix operator+(const Matrix &b) const;

    /**
     * Matrix subtraction
     */
    Matrix operator-(const Matrix &b) const;

    /**
     * Matrix multiplication
     */
    Matrix operator*(const Matrix &b) const;

    /**
     * Scalar multiplication
     */
    Matrix operator*(const float b) const;
    friend Matrix operator*(const float b, const Matrix &a);

    /**
     * Matrix-Vector multiplication
     */
    Vector operator*(const Vector &b) const;

    /**
     * Negative matrix
     */
    Matrix operator-() const;

    Matrix &operator+=(const Matrix &b);
    Matrix &operator-=(const Matrix &b);
    Matrix &operator*=(const Matrix &b);
    Matrix &operator*=(const float b);

    void load_identity();

 private:
    float _mat[4][4];
};  // struct Matrix

/**
 * Scale vector to 1 unit length
 * @param  vec target vector
 * @return     normalized vector
 */
Vector normalize(const Vector &vec);

/**
 * Vector cross production
 * @param  a vector a
 * @param  b vector b
 * @return   a cross b
 */
float cross(const Vector &a, const Vector &b);

/**
 * Vector dot production
 * @param  a vector a
 * @param  b vector b
 * @return   a dot b
 */
float dot(const Vector &a, const Vector &b);

#endif  // RSRL_MATH_H_
