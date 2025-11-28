#include "raylib.h"

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Ma première fenêtre Raylib");
    SetTargetFPS(90);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bravo ! Vous avez initialisé votre projet Raylib !", 110, 280, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
