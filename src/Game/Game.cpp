/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Game
*/

#include "./Game/Game.hpp"
#include <iostream>

Game::Game()
    : _leafs(0), _cps(0), _clickCount(0), _timer(0), _cycleTimer(0), _cycleType(DAY), _shopArea{0, 0, 460, 1080},
      _clickArea{460, 0, 1000, 1080}, _statArea{1460, 0, 460, 1080}
{
    money = 0;
    malusRate = 0.05;
    clientRate = 0.05;
    policeRate = 0.05;
    _raylib = std::make_unique<Raylib>(1920, 1080, "Cookie Clicker");
    srand(time(NULL));
}

Game::~Game()
{
}

void Game::run()
{
    while (!_raylib->windowShouldClose())
    {
        handleEvents();
        update();
        draw();
    }
}

void Game::handleEvents()
{
    Vector2 mousePos = _raylib->getMousePosition();

    if (CheckCollisionPointRec(mousePos, _clickArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        double randomChance = (double)rand() / RAND_MAX;
        if (randomChance <= _tree._leafDropRate)
        {
            _leafs++;
        }
        else
        {
            _leafs += 0;
        }

        _clickCount++;
    }

    if (CheckCollisionPointRec(mousePos, _shopArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout << "Clicked inside the shop area!" << std::endl;
    }
    if (CheckCollisionPointRec(mousePos, _statArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout << "Clicked inside the stats area!" << std::endl;
    }
}
void Game::update()
{
    float dt = _raylib->getFrameTime();
    _timer += dt;
    if (_timer >= 1.0f)
    {
        _cps = _clickCount;
        _clickCount = 0;
        _timer -= 1.0f;
    }
    _cycleTimer += dt;

    switch (_cycleType)
    {
    case DAY:
        if (_cycleTimer >= 180.0f)
        {
            _cycleType = DUSK;
            _cycleTimer = 0;
            std::cout << "Cycle: Passage au Crepuscule" << std::endl;
        }
        break;

    case DUSK:
        if (_cycleTimer >= 30.0f)
        {
            _cycleType = NIGHT;
            _cycleTimer = 0;
            std::cout << "Cycle: Passage a la Nuit" << std::endl;
        }
        break;

    case NIGHT:
        if (_cycleTimer >= 10.0f)
        {
            _cycleType = DAY;
            _cycleTimer = 0;
            std::cout << "Cycle: Retour au Jour" << std::endl;
        }
        break;
    }
}
void Game::draw()
{
    _raylib->beginDrawing();
    _raylib->clearBackground(RAYWHITE);

    Color clickAreaColor;
    switch (_cycleType)
    {
    case DAY:
        clickAreaColor = SKYBLUE;
        break;
    case DUSK:
        clickAreaColor = ORANGE;
        break;
    case NIGHT:
        clickAreaColor = DARKBLUE;
        break;
    default:
        clickAreaColor = LIGHTGRAY;
        break;
    }

    _raylib->drawRectangleRec(_clickArea, clickAreaColor);
    _raylib->drawRectangleRec(_shopArea, BEIGE);
    _raylib->drawRectangleRec(_statArea, RED);

    _raylib->drawText("Shop", _shopArea.x + (_shopArea.width - _raylib->measureText("Shop", 40)) / 2, 20, 40, BLACK);
    Color textColor = (_cycleType == NIGHT) ? WHITE : BLACK;
    _raylib->drawText("Click Here", _clickArea.x + (_clickArea.width - _raylib->measureText("Click Here", 40)) / 2, 20,
                      40, textColor);
    _raylib->drawText("Stat", _statArea.x + (_statArea.width - _raylib->measureText("Stat", 40)) / 2, 20, 40, BLACK);
    drawStats();

    _raylib->endDrawing();
}
void Game::drawStats()
{
    std::vector<std::string> stats;
    stats.push_back("Score: " + std::to_string(_leafs));
    stats.push_back("Clicks per second: " + std::to_string(_cps));

    int yPos = 100;
    int fontSize = 20;
    int padding = 20;
    for (const auto &stat : stats)
    {
        _raylib->drawText(stat, _statArea.x + padding, yPos, fontSize, BLACK);
        yPos += fontSize + 10;
    }
}
