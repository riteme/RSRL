//
// Copyright 2016 riteme
//

#include "Math.h"

#include <iostream>

using namespace std;
using namespace rsr;

int main() {
    float x1, y1, z1, x2, y2, z2, r;

    while (cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r) {
        Vector4f a(x1, y1, z1);
        Vector4f b = { x2, y2, z2 };

        cout << "a + b = " << (a + b).x << ", " << (a + b).y << ", "
             << (a + b).z << endl;
        cout << "a - b = " << (a - b).x << ", " << (a - b).y << ", "
             << (a - b).z << endl;
        cout << "a * r = " << (a * r).x << ", " << (a * r).y << ", "
             << (a * r).z << endl;
        cout << "b * r = " << (r * b).x << ", " << (r * b).y << ", "
             << (r * b).z << endl;
        cout << "-a = " << (-a).x << ", " << (-a).y << ", " << (-a).z << endl;
        cout << "-b = " << (-b).x << ", " << (-b).y << ", " << (-b).z << endl;
        cout << "NORMAL a = " << (normalize(a)).x << ", " << (normalize(a)).y
             << ", " << (normalize(a)).z << endl;
        cout << "NORMAL b = " << (normalize(b)).x << ", " << (normalize(b)).y
             << ", " << (normalize(b)).z << endl;
        cout << "LENGTH a = " << a.length() << endl;
        cout << "LENGTH b = " << b.length() << endl;
    }

    return 0;
}  // function main
