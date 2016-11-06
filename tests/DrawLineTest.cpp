//
// Copyright 2016 riteme
//

#include "Defs.h"
#include "Renderer.h"
#include "Texture.h"
#include "Viewer.h"

#include <cstdlib>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>

using namespace std;
using namespace rsr;

inline int randint(int left, int right) {
    return (rand() % (right - left + 1)) + left;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [N]" << endl;
        return -1;
    }

    int n = atoi(argv[1]);

    ViewWindow window(800, 600);
    Texture texture(800, 600);
    Renderer renderer(&texture);

    srand(time(0));

    vector<int> X1(n), Y1(n), X2(n), Y2(n), SX1(n), SY1(n), SX2(n), SY2(n);
    vector<Color4f> C(n);
    for (int i = 0; i < n; i++) {
        X1[i] = randint(0, 799);
        Y1[i] = randint(0, 599);
        X2[i] = randint(0, 799);
        Y2[i] = randint(0, 599);
        SX1[i] = randint(0, 1) ? 1 : -1;
        SY1[i] = randint(0, 1) ? 1 : -1;
        SX2[i] = randint(0, 1) ? 1 : -1;
        SY2[i] = randint(0, 1) ? 1 : -1;
        C[i] = { randint(175, 255) / 255.0f, randint(0, 55) / 255.0f,
                 randint(35, 125) / 255.0f, 1.0f };
    }

    int count = 0;
    long long lasttime = time(0);
    while (!window.is_closed()) {
        for (int i = 0; i < n; i++) {
            X1[i] += SX1[i];
            Y1[i] += SY1[i];
            X2[i] += SX2[i];
            Y2[i] += SY2[i];

            if (X1[i] < 0) {
                X1[i] = 0;
                SX1[i] *= -1;
            } else if (X1[i] > 799) {
                X1[i] = 799;
                SX1[i] *= -1;
            }

            if (Y1[i] < 0) {
                Y1[i] = 0;
                SY1[i] *= -1;
            } else if (Y1[i] > 599) {
                Y1[i] = 599;
                SY1[i] *= -1;
            }

            if (X2[i] < 0) {
                X2[i] = 0;
                SX2[i] *= -1;
            } else if (X2[i] > 799) {
                X2[i] = 799;
                SX2[i] *= -1;
            }

            if (Y2[i] < 0) {
                Y2[i] = 0;
                SY2[i] *= -1;
            } else if (Y2[i] > 599) {
                Y2[i] = 599;
                SY2[i] *= -1;
            }
        }  // for

        renderer.clear({ 0.0f, 0.0f, 0.0f, 1.0f });

        for (int i = 0; i < n; i++)
            renderer.draw_line(X1[i], Y1[i], X2[i], Y2[i], C[i]);

        // renderer.draw_line(400, 300, 200, 300, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 600, 300, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 400, 100, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 400, 500, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 200, 100, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 200, 500, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 600, 100, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(400, 300, 600, 500, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(200, 100, 600, 100, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(200, 100, 200, 500, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(200, 500, 600, 500, { 1.0f, 1.0f, 1.0f, 1.0f });
        // renderer.draw_line(600, 500, 600, 100, { 1.0f, 1.0f, 1.0f, 1.0f });

        renderer.apply();

        window.update(texture);
        window.do_events();

        if (time(0) != lasttime) {
            cout << "FPS: " << count << endl;
            lasttime = time(0);
            count = 0;
        } else
            count++;
    }

    return 0;
}
