namespace RLB {
    #include "raylib/raylib.h"
}

#include "headers/player.h"
#include "headers/platform.h"

#define WIDTH 1000
#define HEIGHT 650
#define TARGET_FPS 60
#define SCALE_FACTOR 5
#define GRAVITY 1

int main(void) {
    RLB::InitWindow(WIDTH, HEIGHT, "Lil Man's Adventure");
    RLB::SetTargetFPS(TARGET_FPS);

    Platform platform = Platform(SCALE_FACTOR, 300, 400);
    Player player = Player(SCALE_FACTOR, GRAVITY);

    while (!RLB::WindowShouldClose()) {
        RLB::BeginDrawing();
            RLB::ClearBackground({0, 0, 0, 255});

            platform.draw();

            player.update(platform.hitbox);
            player.draw();

        RLB::EndDrawing();
    }

    RLB::CloseWindow();

    return 0;
}