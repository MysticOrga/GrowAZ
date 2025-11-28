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
    Object obj1(StatBuff::LEAF_DROP, 0.01, "Leaf Booster", 100);
    Object obj2(StatBuff::TREE_SIZE, 0.02, "Tree Size", 500);
    money = 0;
    malusRate = 0.05;
    clientRate = 0.05;
    policeRate = 0.01;
    policeAlert = false;
    _raylib = std::make_unique<Raylib>(1920, 1080, "Cookie Clicker");
    srand(time(NULL));
    _shop.addObject(obj1);
    _shop.addObject(obj2);
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

void Game::handleBuffing(const Object obj)
{
    switch (obj.getStatToBuff())
    {
    case StatBuff::LEAF_DROP:
        _tree._leafDropRate += obj.getBuff();
        std::cout << "Leaf drop: " << _tree._leafDropRate << std::endl;
        break;
    case StatBuff::TREE_SIZE:
        _tree._height += obj.getBuff();
        std::cout << "tree size: " << _tree._height << std::endl;
        break;
    case StatBuff::CLIENT_DROP:
        clientRate += obj.getBuff();
        break;
    case StatBuff::MALUS_DROP:
        malusRate += obj.getBuff();
        break;
    case StatBuff::COPS_DROP:
        policeRate += obj.getBuff();
        break;
    default:
        break;
    }
}

void Game::handleEvents()
{
    Vector2 mousePos = _raylib->getMousePosition();

    if (CheckCollisionPointRec(mousePos, _clickArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        _cycleType == DAY)
    {
        double randomChance = (double)rand() / RAND_MAX;
        _cycleTimer += 2.0f;
        if (randomChance <= (_tree._leafDropRate + _tree._height))
        {
            _leafs++;
        }
        else
        {
            _leafs += 0;
        }

        _clickCount++;
    }

    if (CheckCollisionPointRec(mousePos, _shopArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        _cycleType == DUSK && policeAlert == false)
    {
        std::cout << "Clicked inside the shop area!" << std::endl;
    }
    if (CheckCollisionPointRec(mousePos, _statArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        std::cout << "Clicked inside the stats area!" << std::endl;
    }

    int yPos = 100;
    for (const auto &itemPair : _shop.getObjectList())
    {
        Rectangle itemButton = {_shopArea.x + 20, (float)yPos, _shopArea.width - 40, 50};
        if (CheckCollisionPointRec(mousePos, itemButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            _cycleType == DUSK && policeAlert == false)
        {
            Object boughtObject;
            std::cout << "Trying to buy: " << itemPair.first << std::endl;
            if (_shop.buyObject(itemPair.first, boughtObject, money))
                this->handleBuffing(boughtObject);
        }
        yPos += 60;
    }

    Rectangle sellButton = {_statArea.x + _statArea.width - 220, _statArea.height - 70, 200, 50};
    if (CheckCollisionPointRec(mousePos, sellButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        _cycleType == DUSK && policeAlert == false)
    {
        if (_leafs > 0)
        {
            _leafs--;
            money += 100;
            std::cout << "Vendu 1 feuille pour 100$. Argent actuel: " << money << std::endl;
        }
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
        if (_cycleTimer >= 60.0f)
        {
            _cycleType = DUSK;
            _cycleTimer = 0;
            std::cout << "Cycle: Passage au Crepuscule" << std::endl;
        } else {
            double randomPolice = (double)rand() / RAND_MAX;
            if (randomPolice < policeRate + _tree._height + malusRate) {
                policeAlert = true;
            }
        }
        break;

    case DUSK:
        if (_cycleTimer >= 45.0f)
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
            policeAlert = false;
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
    drawShop();

    Rectangle sellButton = {_statArea.x + _statArea.width - 220, _statArea.height - 70, 200, 50};
    Color buttonColor = (_leafs > 0) ? LIME : GRAY;
    _raylib->drawRectangleRec(sellButton, buttonColor);
    std::string sellText = "Vendre Feuille (100)";
    int textWidth = _raylib->measureText(sellText, 20);
    _raylib->drawText(sellText, sellButton.x + (sellButton.width - textWidth) / 2, sellButton.y + 15, 20, BLACK);

    _raylib->endDrawing();
}

void Game::drawShop()
{
    int yPos = 100;
    int fontSize = 20;
    for (const auto &itemPair : _shop.getObjectList())
    {
        Rectangle itemButton = {_shopArea.x + 20, (float)yPos, _shopArea.width - 40, 50};
        _raylib->drawRectangleRec(itemButton, LIGHTGRAY);
        _raylib->drawText(itemPair.first.c_str(), itemButton.x + 10, itemButton.y + 15, fontSize, BLACK);
        std::string priceText = std::to_string(itemPair.second) + " $";
        _raylib->drawText(priceText, itemButton.x + itemButton.width - _raylib->measureText(priceText, fontSize) - 10,
                          itemButton.y + 15, fontSize, DARKGREEN);
        yPos += 60;
    }
}

void Game::drawStats()
{
    std::vector<std::string> stats;
    stats.push_back("Score: " + std::to_string(_leafs));
    stats.push_back("Clicks per second: " + std::to_string(_cps));
    stats.push_back("Money: " + std::to_string(money) + " $");
    stats.push_back("Drop Rate: " + std::to_string(_tree._leafDropRate * 100) + " %");
    if (policeAlert) {
        stats.push_back("Police Alert: YES");
    } else {
        stats.push_back("Police Alert: NO");
    }

    int yPos = 100;
    int fontSize = 20;
    int padding = 20;
    for (const auto &stat : stats)
    {
        _raylib->drawText(stat, _statArea.x + padding, yPos, fontSize, BLACK);
        yPos += fontSize + 10;
    }
}
