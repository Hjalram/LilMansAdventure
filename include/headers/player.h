#pragma once

namespace RLB {
    #include "raylib/raylib.h"
}
#include "headers/hitbox.h"

class Player {
public:
    RLB::Vector2 position;
    RLB::Vector2 velocity;
    int pixelWidth, pixelHeight;
    int trueWidth, trueHeight;
    float maxWalkSpeed;
    float gravity;
    float scaleFactor;

    RLB::Texture2D spritesheet;

    Hitbox hitbox;

    Player(float _scale, float _gravity) {
        position.x = 300;
        position.y = 100;
        velocity.x = 0;
        velocity.y = 0;
        pixelWidth = 16;
        pixelHeight = 16;
        scaleFactor = _scale;
        gravity = _gravity;
        maxWalkSpeed = 10;
        trueWidth = pixelWidth*scaleFactor;
        trueHeight = pixelHeight*scaleFactor;

        hitbox = Hitbox(position.x, position.y, trueWidth, trueHeight);

        spritesheet = RLB::LoadTexture("../build/assets/lilmansheet.png");
    }

    void update() {
        if (RLB::IsKeyDown(RLB::KEY_RIGHT)) {
            velocity.x = maxWalkSpeed;
        }
        if (RLB::IsKeyDown(RLB::KEY_LEFT)) {
            velocity.x = -maxWalkSpeed;
        }
        if (RLB::IsKeyUp(RLB::KEY_LEFT) && RLB::IsKeyUp(RLB::KEY_RIGHT)) {
            velocity.x = 0;
        }

        velocity.y += gravity;
        position.x += velocity.x;
        position.y += velocity.y;

        hitbox.position.x = position.x;
        hitbox.position.y = position.y;
        hitbox.width = trueWidth - scaleFactor*11;
        hitbox.height = trueHeight - scaleFactor*2;
    }

    void draw() {
        RLB::Rectangle source = (RLB::Rectangle){0, 0, (float)pixelWidth, (float)pixelHeight};
        RLB::Rectangle dest = (RLB::Rectangle){position.x, position.y, (float)trueWidth, (float)trueHeight};
        RLB::DrawTexturePro(spritesheet, source, dest, (RLB::Vector2){scaleFactor*5, scaleFactor*2}, 0, RLB::WHITE);

        hitbox.draw();
    }
};