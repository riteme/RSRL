//
// Copyright 2016 riteme
//

#include "Math.h"

#include <cstddef>

#include <iostream>

using namespace std;
using namespace rsr;

bool read_matrix(Matrix &a) {
    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            cin >> a[i][j];

    return cin.good();
}

void print_matrix(const string &message, const Matrix &a) {
    cout << message << endl;

    for (size_t i = 0; i < 4; i++) {
        cout << "\t";

        for (size_t j = 0; j < 4; j++) {
            cout << a[i][j] << " ";
        }

        cout << endl;
    }
}

int main() {
    Matrix a, b;
    float r;

    while (read_matrix(a) && read_matrix(b) && cin >> r) {
        print_matrix("a + b =", a + b);
        print_matrix("a - b =", a - b);
        print_matrix("a * b =", a * b);
        print_matrix("a * r =", a * r);
        print_matrix("b * r =", r * b);
    }  // while

    return 0;
}  // function main
