#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "ORK Test");

    // Correct filename (case-sensitive!)
    Texture2D ork = LoadTexture("assets/3_ORK/ORK_03_ARRAK_000.png");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(ork, 400, 300, WHITE); // draw your monster
        EndDrawing();
    }

    UnloadTexture(ork);
    CloseWindow();
    return 0;
}
