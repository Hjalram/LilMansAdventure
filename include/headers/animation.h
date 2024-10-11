#pragma once

#include "raylib/rlb.h"

#include <vector>

class Animation {
public:
    std::vector<int> frameIndexes;
    int frameDuration;
    const char* state;

    Animation(const char* _state, std::vector<int> _frameIndexes, int _frameDuration) {
        frameIndexes = _frameIndexes;
        frameDuration = _frameDuration;
        state = _state;
    }
    Animation() = default;
};