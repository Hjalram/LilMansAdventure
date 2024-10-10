namespace RLB {
    #include "raylib/raylib.h"
}

int main(void) {
    int WIDTH = 1000;
    int HEIGHT = 650;
    int TARGET_FPS = 60;

    RLB::InitWindow(WIDTH, HEIGHT, "Lil Man's Adventure");
    RLB::SetTargetFPS(TARGET_FPS);

    while (!RLB::WindowShouldClose()) {
        RLB::BeginDrawing();
            RLB::ClearBackground({230, 230, 230, 255});
            RLB::DrawRectangle(200, 200, 50, 50, RLB::BLACK);
        RLB::EndDrawing();
    }

    return 0;
}