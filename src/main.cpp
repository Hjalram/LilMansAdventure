namespace RLB {
    #include "raylib/raylib.h"
}

#define WIDTH 1000
#define HEIGHT 650
#define TARGET_FPS 60

class Player {
public:
    RLB::Vector2 position;
    int width, height;

    RLB::Texture2D spritesheet;

    Player() {
        position.x = 100;
        position.y = 100;
        width = 50;
        height = 50;

        spritesheet = RLB::LoadTexture("../build/assets/lilmansheet.png");
    }

    void draw() {
        RLB::Rectangle source = (RLB::Rectangle){0, 0, 16, 16};
        RLB::Rectangle dest = (RLB::Rectangle){position.x, position.y, 64, 64};
        RLB::DrawTexturePro(spritesheet, source, dest, (RLB::Vector2){0, 0}, 0, RLB::WHITE);
    }
};

int main(void) {
    RLB::InitWindow(WIDTH, HEIGHT, "Lil Man's Adventure");
    RLB::SetTargetFPS(TARGET_FPS);

    Player player = Player();

    while (!RLB::WindowShouldClose()) {
        RLB::BeginDrawing();
            RLB::ClearBackground({0, 0, 0, 255});

            player.draw();

        RLB::EndDrawing();
    }

    return 0;
}