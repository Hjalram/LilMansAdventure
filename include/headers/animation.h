#pragma once

namespace RLB {
    #include "raylib/raylib.h"
}
#include <vector>

class Animation {
public:
    std::vector<int> frameIndexes;
    int frameDuration;

    Animation(std::vector<int> _frameIndexes, int _frameDuration) {
        frameIndexes = _frameIndexes;
        frameDuration = _frameDuration;
    }
    Animation() = default;
};