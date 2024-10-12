#pragma once

#include "raylib/rlb.h"
#include "headers/hitbox.h"
#include "headers/animation.h"
#include "headers/level.h"
#include <vector>
#include <cmath>

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
    bool onGround;

    RLB::Texture2D spritesheet;

    Hitbox hitbox;
    Animation idle;
    Animation walk;
    
    const char* currentAnimationState;
    
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
        onGround = false;

        currentFrameList = 0;
        frameCounter = 0;

        hitbox = Hitbox(position.x, position.y, trueWidth, trueHeight);
        idle = Animation("walk", {0, 1}, 60);
        walk = Animation("idle", {2, 3, 4, 5}, 5);

        spritesheet = RLB::LoadTexture("./assets/lilmansheet.png");
    }

    void playAnimation(Animation _animation) {
        if (currentAnimationState != _animation.state) {
            currentFrameList = 0;
        }

        currentAnimationState = _animation.state;

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
        if (RLB::IsKeyDown(RLB::KEY_RIGHT)) {
            velocity.x = maxWalkSpeed;
        }
        if (RLB::IsKeyDown(RLB::KEY_LEFT)) {
            velocity.x = -maxWalkSpeed;
        }
        if (RLB::IsKeyUp(RLB::KEY_LEFT) && RLB::IsKeyUp(RLB::KEY_RIGHT)) {
            velocity.x = 0;
        }
        if (RLB::IsKeyPressed(RLB::KEY_UP) && groundCheck(_level.platforms)) {
            velocity.y = jumpForce;
        }

        if (!groundCheck(_level.platforms)) {
            velocity.y += gravity;
        }

        collide(_level.platforms);

        // Updating hitbox position
        if (!xFlipped) {position.x = hitbox.position.x;} // Correct for the fact that is hitbox sometimes is off center
        else {position.x = hitbox.position.x - 1*scaleFactor;}        
        position.y = hitbox.position.y;

        hitbox.height = trueHeight - scaleFactor*2;
        hitbox.width = trueWidth - scaleFactor*11;

        if (velocity.x > 0) {
            xFlipped = false;
        }
        if (velocity.x < 0) {
            xFlipped = true;
        }
    }

    bool groundCheck(std::vector<Platform> _platforms) {
        for (int i = 0; i < (int)_platforms.size(); i++) {
            Hitbox other = _platforms[i].hitbox;

            if (hitbox.position.x + hitbox.width > other.position.x && // x collision
            hitbox.position.x < other.position.x + other.width) 
            {
                if (hitbox.position.y == other.position.y - hitbox.height) {
                    return true;
                }
            }
        }

        return false;
    }

    void collisionCheck(const std::vector<Platform> _in, std::vector<Platform> &_out) {
        for (int i = 0; i < (int)_in.size(); i++) {
            Hitbox other = _in[i].hitbox;

            if (hitbox.position.y + hitbox.height > other.position.y && 
                hitbox.position.y < other.position.y + other.height &&
                hitbox.position.x + hitbox.width > other.position.x && 
                hitbox.position.x < other.position.x + other.width) 
            {
                _out.push_back(_in[i]);
            }
        }
    } 

    void collide(std::vector<Platform> _platforms) {
        std::vector<Platform> collisions;

        hitbox.position.x += velocity.x;
        collisionCheck(_platforms, collisions);
        for (int i = 0; i < (int)collisions.size(); i++) {
            Hitbox tile = collisions[i].hitbox;

            if (velocity.x > 0) { // Collision from the left
                hitbox.position.x = tile.position.x - hitbox.width;
                velocity.x = 0;
            }
            if (velocity.x < 0) { // Collision from the right
                hitbox.position.x = tile.position.x + tile.width;
                velocity.x = 0;
            }
        }
        
        collisions.clear();
        hitbox.position.y += velocity.y;
        collisionCheck(_platforms, collisions);
        for (int i = 0; i < (int)collisions.size(); i++) {
            Hitbox tile = collisions[i].hitbox;

            if (velocity.y > 0) { // Collision from the above
                hitbox.position.y = tile.position.y - hitbox.height;
                velocity.y = 0;
            }
            if (velocity.y < 0) { // Collision from underneath
                hitbox.position.y = tile.position.y + tile.height;
                velocity.y = 0;
            }
        }


        /*if (hitbox.position.y + hitbox.height > other.position.y && 
            hitbox.position.x + hitbox.width > other.position.x && 
            hitbox.position.x < other.position.x + other.width) {
            position.y = other.position.y - hitbox.height;
            velocity.y = 0;
        }*/
    }

    void draw() {
        if (velocity.x != 0) {
            playAnimation(walk);
        }
        else {
            playAnimation(idle);
        }
        
        //hitbox.draw();
    }
};