#include "Game.hpp"

Game::Game(int width, int height)
    : screenWidth(width), screenHeight(height), tree({width / 2.0f, height / 2.0f}, 120.0f, 60.0f, 180.0f), rng(std::random_device{}()), dropDist(0.0f, 1.0f)
{
}

void Game::run()
{
    InitWindow(screenWidth, screenHeight, "GrowAZ");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        handleInput();
        update(dt);
        draw();
    }

    CloseWindow();
}

void Game::handleInput()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (tree.contains(mouse)) {
            if (rollDrop()) {
                leaves += 1;
                floatingTexts.spawn(mouse, "+1");
            }
        }
    }
}

void Game::update(float dt)
{
    tree.animate(dt);
    floatingTexts.update(dt);
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    tree.draw();
    drawUI();
    floatingTexts.draw();

    EndDrawing();
}

void Game::drawUI()
{
    std::string leavesText = "Leaves: " + std::to_string(leaves);
    DrawText(leavesText.c_str(), 20, 20, 24, DARKGREEN);
}

bool Game::rollDrop()
{
    float dropChance = 0.35f;
    return dropDist(rng) <= dropChance;
}
