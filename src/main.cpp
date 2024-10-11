#include "raylib/rlb.h"
#include "headers/player.h"
#include "headers/platform.h"
#include "headers/level.h"

#define WIDTH 1000
#define HEIGHT 650
#define TARGET_FPS 60
#define SCALE_FACTOR 5
#define GRAVITY 1

int main(void) {
    RLB::InitWindow(WIDTH, HEIGHT, "Lil Man's Adventure");
    RLB::SetTargetFPS(TARGET_FPS);

    Level level = Level({
        Platform(SCALE_FACTOR, 300, 400),
        Platform(SCALE_FACTOR, 500, 280),
        Platform(SCALE_FACTOR, 0, 270)
    });

    Player player = Player(SCALE_FACTOR, GRAVITY);

    while (!RLB::WindowShouldClose()) {
        RLB::BeginDrawing();
            RLB::ClearBackground({0, 0, 0, 255});

            level.draw();

            player.update(level);
            player.draw();

        RLB::EndDrawing();
    }

    RLB::CloseWindow();

    return 0;
}