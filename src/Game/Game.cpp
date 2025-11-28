/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Game
*/

#include "./Game/Game.hpp"
#include <iostream>

Game::Game() : _score(0)
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
    if (_raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        _score += 1;
        std::cout << "Score: " << _score << std::endl;
    }
}

void Game::update()
{
}

void Game::draw()
{
    _raylib->beginDrawing();
    _raylib->clearBackground(RAYWHITE);
    _raylib->drawText("Score: " + std::to_string(_score), 10, 10, 20, BLACK);
    _raylib->endDrawing();
}
