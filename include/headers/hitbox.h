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

    void collide(RLB::Vector2 &_position, RLB::Vector2 &_velocity, Hitbox other) {
        if (position.y + height > other.position.y) {
            _position.y = other.position.y - height;
            _velocity.y = 0;
        }
    }

    void draw() {
        RLB::DrawRectangleLines(position.x, position.y, width, height, RLB::GREEN);
    }
};