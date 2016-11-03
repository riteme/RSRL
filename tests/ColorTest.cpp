//
// Copyright 2016 riteme
//

#include <iostream>

#include "Color.h"

using namespace std;

int main() {
    float r1, g1, b1, a1;
    float r2, g2, b2, a2;
    float r;

    while (cin >> r1 >> g1 >> b1 >> a1 >> r2 >> g2 >> b2 >> a2 >> r) {
        Color a(r1, g1, b1, a1);
        Color b(r2, g2, b2, a2);

        Color c = a + b;
        cout << "a + b = " << c.red << ", " << c.green << ", " << c.blue << ", "
             << c.alpha << endl;
        c = a * r;
        cout << "a * r = " << c.red << ", " << c.green << ", " << c.blue << ", "
             << c.alpha << endl;
        c = b * r;
        cout << "b * r = " << c.red << ", " << c.green << ", " << c.blue << ", "
             << c.alpha << endl;

        cout << "-a = " << (-a).red << ", " << (-a).green << ", " << (-a).blue
             << ", " << (-a).alpha << endl;
        cout << "-b = " << (-b).red << ", " << (-b).green << ", " << (-b).blue
             << ", " << (-b).alpha << endl;
    }  // while

    return 0;
}  // function main
