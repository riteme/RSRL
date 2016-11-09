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

int main(int argc, char *argv[]) {
    ViewWindow window(800, 600);
    Texture texture(800, 600);
    Renderer renderer(&texture);

    int count = 0;
    long long lasttime = time(0);
    while (!window.is_closed()) {
        renderer.clear({ 0.0f, 0.0f, 0.0f, 1.0f });

        int mx, my;
        SDL_GetMouseState(&mx, &my);
        renderer._draw_left_triangle(100, 500, 400, mx, my,
                                     { 0.0f, 1.0f, 0.0f, 1.0f });
        renderer._draw_right_triangle(100, 500, 400, mx, my,
                                      { 1.0f, 0.0f, 0.0f, 1.0f });

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
