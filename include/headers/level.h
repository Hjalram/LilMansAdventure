#pragma once

#include "raylib/rlb.h"
#include "headers/platform.h"
#include <vector>

class Level {
public:
    std::vector<Platform> platforms;

    Level(std::vector<Platform> _platforms) {
        platforms = _platforms;
    }

    void draw() {
        for (int i = 0; i < (int)platforms.size(); i++) {
            Platform platform = platforms[i];
            platform.draw();
        }
    }
};