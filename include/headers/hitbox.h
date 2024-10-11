#pragma once

namespace RLB {
    #include "raylib/raylib.h"
}

class Hitbox {
public:
    RLB::Vector2 position;
    int width, height;

    Hitbox(int _x, int _y, int _w, int _h) {
        position.x = _x;
        position.y = _y;
        width = _w;
        height = _h;
    }
    Hitbox() = default;

    void draw() {
        RLB::DrawRectangleLines(position.x, position.y, width, height, RLB::GREEN);
    }
};