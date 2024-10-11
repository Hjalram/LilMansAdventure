#pragma once

#include "raylib/rlb.h"
#include "headers/hitbox.h"
#include "headers/animation.h"
#include "headers/level.h"
#include <vector>

class Player {
public:
    RLB::Vector2 position;
    RLB::Vector2 velocity;
    int pixelWidth, pixelHeight;
    int trueWidth, trueHeight;
    float maxWalkSpeed;
    float jumpForce;
    float gravity;
    float scaleFactor;

    bool xFlipped;

    RLB::Texture2D spritesheet;

    Hitbox hitbox;
    Animation idle;
    Animation walk;
    
    int currentFrameList;
    int currentFrameSheet;
    int frameCounter;

    Player(float _scale, float _gravity) {
        position.x = 300;
        position.y = 100;
        velocity.x = 0;
        velocity.y = 0;
        pixelWidth = 16;
        pixelHeight = 16;
        scaleFactor = _scale;
        gravity = _gravity;
        maxWalkSpeed = 7;
        jumpForce = -15;
        trueWidth = pixelWidth*scaleFactor;
        trueHeight = pixelHeight*scaleFactor;
        xFlipped = false;

        currentFrameList = 0;
        frameCounter = 0;

        hitbox = Hitbox(position.x, position.y, trueWidth, trueHeight);
        idle = Animation({0, 1}, 60);
        walk = Animation({2, 3, 4, 5}, 5);

        spritesheet = RLB::LoadTexture("../build/assets/lilmansheet.png");
    }

    void playAnimation(Animation _animation) {
        // DRAW THE CURRENT FRAME
        float flipped;
        if (!xFlipped) {flipped = pixelWidth;}
        else {flipped = -pixelWidth;}

        currentFrameSheet = _animation.frameIndexes[currentFrameList];

        RLB::Rectangle source = (RLB::Rectangle){(float)currentFrameSheet*pixelWidth, 0, flipped, (float)pixelHeight};
        RLB::Rectangle dest = (RLB::Rectangle){position.x, position.y, (float)trueWidth, (float)trueHeight};
        RLB::DrawTexturePro(spritesheet, source, dest, (RLB::Vector2){scaleFactor*5, scaleFactor*2}, 0, RLB::WHITE);

        // ADVANCE THE FRAME COUNTER
        frameCounter += 1;

        if (frameCounter >= _animation.frameDuration) {
            currentFrameList += 1;
            frameCounter = 0;
        }
        if (currentFrameList > (int)_animation.frameIndexes.size() - 1) {
            currentFrameList = 0;
        }
    }

    void update(Level _level) {
        for (int i = 0; i < (int)_level.platforms.size(); i++) {
            hitbox.collide(position, velocity, _level.platforms[i].hitbox);
        }

        if (RLB::IsKeyDown(RLB::KEY_RIGHT)) {
            velocity.x = maxWalkSpeed;
        }
        if (RLB::IsKeyDown(RLB::KEY_LEFT)) {
            velocity.x = -maxWalkSpeed;
        }
        if (RLB::IsKeyUp(RLB::KEY_LEFT) && RLB::IsKeyUp(RLB::KEY_RIGHT)) {
            velocity.x = 0;
        }
        if (RLB::IsKeyPressed(RLB::KEY_UP)) {
            velocity.y = jumpForce;
        }

        velocity.y += gravity;
        position.x += velocity.x;
        position.y += velocity.y;

        if (!xFlipped) {hitbox.position.x = position.x;} // Correct for the fact that is hitbox sometimes is off center
        else {hitbox.position.x = position.x + scaleFactor;}
        hitbox.position.y = position.y;
        hitbox.height = trueHeight - scaleFactor*2;
        hitbox.width = trueWidth - scaleFactor*11;

        if (velocity.x > 0) {
            xFlipped = false;
        }
        if (velocity.x < 0) {
            xFlipped = true;
        }
    }

    void draw() {
        if (velocity.x != 0) {
            playAnimation(walk);
        }
        else {
            playAnimation(idle);
        }
        
        hitbox.draw();
    }
};