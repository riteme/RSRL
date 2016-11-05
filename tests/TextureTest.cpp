//
// Copyright 2016 riteme
//

#include "Texture.h"
#include "Defs.h"
#include "Viewer.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

using namespace std;
using namespace rsr;

int main() {
    ViewWindow window(800, 600);
    Texture texture(800, 600);

    srand(time(0));

    Color background = {0.5f, 0.5f, 0.5f, 1.0f};
    float rv = ((rand() % 200) - 100) / 10000.0f;
    float gv = ((rand() % 200) - 100) / 10000.0f;
    float bv = ((rand() % 200) - 100) / 10000.0f;

    cout << "rv = " << rv << ", gv = " << gv << ", bv = " << bv << endl;

    int count = 0;
    long long lasttime = time(0);

    while (!window.is_closed()) {
        background.red += rv;
        background.green += gv;
        background.blue += bv;

        if (background.red <= 0.0f || background.red >= 1.0f)
            rv *= -1.0f;
        if (background.green <= 0.0f || background.green >= 1.0f)
            gv *= -1.0f;
        if (background.blue <= 0.0f || background.blue >= 1.0f)
            bv *= -1.0f;

        texture.clear(background);
        for (int x = 200; x <= 600; x++)
            for (int y = 200; y <= 400; y++)
                texture[x][y] = -background;

        SDL_Surface *data;
        texture.read_data(data);
        window.update(data);
        SDL_FreeSurface(data);

        window.render();

        if (time(0) != lasttime) {
            cout << "FPS: " << count << endl;
            lasttime = time(0);
            count = 0;
        } else
            count++;
    }

    return 0;
}
