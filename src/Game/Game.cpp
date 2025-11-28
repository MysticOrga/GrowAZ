/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Game
*/

#include "./Game/Game.hpp"
#include <iostream>

Game::Game() : _score(0), _cps(0), _clickCount(0), _timer(0),
               _shopArea{ 0, 0, 460, 1080 },
               _clickArea{ 460, 0, 1000, 1080 },
               _statArea{ 1460, 0, 460, 1080 }
{
    _raylib = std::make_unique<Raylib>(1920, 1080, "Cookie Clicker");
}

Game::~Game()
{
}

void Game::run()
{
    while (!_raylib->windowShouldClose()) {
        handleEvents();
        update();
        draw();
    }
}

void Game::handleEvents()
{
    Vector2 mousePos = _raylib->getMousePosition();

    if (CheckCollisionPointRec(mousePos, _clickArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        _score++;
        _clickCount++;
    }
    if (CheckCollisionPointRec(mousePos, _shopArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "Clicked inside the shop area!" << std::endl;
    }
    if (CheckCollisionPointRec(mousePos, _statArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "Clicked inside the stats area!" << std::endl;
    }
}

void Game::update()
{
    _timer += _raylib->getFrameTime();
    if (_timer >= 1.0f) {
        _cps = _clickCount;
        _clickCount = 0;
        _timer -= 1.0f;
    }
}

void Game::draw()
{
    _raylib->beginDrawing();
    _raylib->clearBackground(RAYWHITE);

    _raylib->drawRectangleRec(_clickArea, LIGHTGRAY);
    _raylib->drawRectangleRec(_shopArea, BEIGE);
    _raylib->drawRectangleRec(_statArea, RED);

    _raylib->drawText("Shop", _shopArea.x + (_shopArea.width - _raylib->measureText("Shop", 40)) / 2, 20, 40, BLACK);
    _raylib->drawText("Click Here", _clickArea.x + (_clickArea.width - _raylib->measureText("Click Here", 40)) / 2, 20, 40, BLACK);
    _raylib->drawText("Stat", _statArea.x + (_statArea.width - _raylib->measureText("Stat", 40)) / 2, 20, 40, BLACK);
    drawStats();

    _raylib->endDrawing();
}

void Game::drawStats()
{
    std::vector<std::string> stats;
    stats.push_back("Score: " + std::to_string(_score));
    stats.push_back("Clicks per second: " + std::to_string(_cps));
    // Vous pouvez ajouter autant de stats que vous voulez ici
    // stats.push_back("Autre stat: " + std::to_string(valeur));

    int yPos = 100;
    int fontSize = 20;
    int padding = 20;
    for (const auto& stat : stats) {
        _raylib->drawText(stat, _statArea.x + padding, yPos, fontSize, BLACK);
        yPos += fontSize + 10;
    }
}
