#pragma once

#include "raylib/rlb.h"
#include "headers/hitbox.h"

class Platform {
public:
    RLB::Vector2 position;
    int pixelWidth, pixelHeight;
    int trueWidth, trueHeight;
    float scaleFactor;

    RLB::Texture2D platformImage;
    Hitbox hitbox;

    Platform(float _scale, int _x, int _y) {
        position.x = _x;
        position.y = _y;
        scaleFactor = _scale;
        pixelWidth = 48;
        pixelHeight = 16;
        trueWidth = pixelWidth*scaleFactor;
        trueHeight = pixelHeight*scaleFactor;

        hitbox = Hitbox(position.x, position.y, trueWidth, trueHeight);

        platformImage = RLB::LoadTexture("../build/assets/lilmanplatform.png");
    }

    void draw() {
        RLB::Rectangle source = (RLB::Rectangle){0, 0, (float)pixelWidth, (float)pixelHeight};
        RLB::Rectangle dest = (RLB::Rectangle){position.x, position.y, (float)trueWidth, (float)trueHeight};
        RLB::DrawTexturePro(platformImage, source, dest, (RLB::Vector2){0, 0}, 0, RLB::WHITE);

        hitbox.draw();
    }
};