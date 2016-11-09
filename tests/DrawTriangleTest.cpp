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
    ViewWindow window(800, 600);
    Texture texture(800, 600);
    Renderer renderer(&texture);

    int count = 0;
    long long lasttime = time(0);

    int x1 = randint(0, 799);
    int y1 = randint(0, 599);
    int sx1 = randint(0, 1) ? 1 : -1;
    int sy1 = randint(0, 1) ? 1 : -1;
    int x2 = randint(0, 799);
    int y2 = randint(0, 599);
    int sx2 = randint(0, 1) ? 1 : -1;
    int sy2 = randint(0, 1) ? 1 : -1;

    while (!window.is_closed()) {
        renderer.clear({0.0f, 0.0f, 0.0f, 1.0f});

        x1 += sx1;
        y1 += sy1;
        x2 += sx2;
        y2 += sy2;

        if (x1 < 0) {
            x1 = 0;
            sx1 *= -1;
        } else if (x1 > 799) {
            x1 = 799;
            sx1 *= -1;
        }

        if (y1 < 0) {
            y1 = 0;
            sy1 *= -1;
        } else if (y1 > 599) {
            y1 = 599;
            sy1 *= -1;
        }

        if (x2 < 0) {
            x2 = 0;
            sx2 *= -1;
        } else if (x2 > 799) {
            x2 = 799;
            sx2 *= -1;
        }

        if (y2 < 0) {
            y2 = 0;
            sy2 *= -1;
        } else if (y2 > 599) {
            y2 = 599;
            sy2 *= -1;
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);
        renderer.draw_triangle(x1, y1, x2, y2, mx, my,
                               {1.0f, 0.5f, 0.5f, 1.0f});

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
