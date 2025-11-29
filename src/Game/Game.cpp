/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Game
*/

#include "./Game/Game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
    : _leafs(0), _cps(0), _clickCount(0), _timer(0), _cycleTimer(0), _cycleType(DAY), _shopArea{0, 0, 460, 1080},
        _clickArea{460, 0, 1000, 1080}, _statArea{1460, 0, 460, 1080}, _running(true), _gameState(GameState::MENU),
        _playButton{760, 380, 400, 80}, _loadButton{760, 480, 400, 80}, _quitButton{760, 580, 400, 80}
{
    Object obj1(StatBuff::LEAF_DROP, 0.01, "Leaf Booster", 100);
    Object obj2(StatBuff::TREE_SIZE, 1, "Tree Size", 500);
    Object emp1(StatBuff::AUTO_CLICK, 0.01, "Collector", 650);
    Malus m1(MalusType::LEAF, 200, "Thief");

    money = 0;
    malusRate = 0.05;
    clientRate = 0.05;
    policeRate = 0.01;
    policeAlert = false;
    _tree._height = 1;
    _tree._leafDropRate = 0.01;
    _raylib = std::make_unique<Raylib>(1920, 1080, "Cookie Clicker");
    srand(time(NULL));
    _shop.addObject(obj1);
    _shop.addObject(obj2);
    _shop.addObject(emp1);
    dayWeek = 1;
    debt = 50000;
    _malus.push_back(m1);
    _sellButtonHovered = false;
    _particleSystem.init(500);
    _pauseButton = {_statArea.x + _statArea.width - 180, 20, 160, 40};
    _pauseButtonHovered = false;
    _pauseSaveButton = {(float)((1920 - 200) / 2), 520, 200, 60};
    _pauseQuitButton = {(float)((1920 - 200) / 2), 600, 200, 60};
    _pauseSaveButtonHovered = false;
    _pauseQuitButtonHovered = false;
    _screenCamera.offset = { 0.0f, 0.0f };
    _screenCamera.target = { 0.0f, 0.0f };
    _screenCamera.rotation = 0.0f;
    _screenCamera.zoom = 1.0f;
    _shakeTimer = 0.0f;
    _shakeIntensity = 0.0f;
    // InitAudioDevice();
    // menu_music = LoadMusicStream("../soundboard/Menu_sound.mp3");
    // PlayMusicStream(menu_music);
    this->_raylib->loadTexture("tree", "../SpriteSheet/tree.png");
    _leafTexture = LoadTexture("../SpriteSheet/falling_leaf.png");
    // 2. On prépare un pool de 200 feuilles (elles sont invisibles pour l'instant)
    for (int i = 0; i < 200; i++) {
        FallingLeaf leaf;
        leaf.pos = { -100.0f, -100.0f }; // Hors écran
        leaf.speed = 0;
        _rainLeaves.push_back(leaf);
    }
}

Game::~Game()
{
    // UnloadMusicStream(menu_music);
    // CloseAudioDevice();
}

void Game::run()
{
    while (_running && !_raylib->windowShouldClose())
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
    case StatBuff::AUTO_CLICK:
        _employee.push_back(obj);
        break;
    default:
        break;
    }
}

void Game::handleEvents()
{
    Vector2 mousePos = _raylib->getMousePosition();
    _pauseButtonHovered = false;
    _pauseSaveButtonHovered = false;
    _pauseQuitButtonHovered = false;

    if (_gameState == GameState::MENU) {
        if (CheckCollisionPointRec(mousePos, _playButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
            _gameState = GameState::RUNNING;
        if (CheckCollisionPointRec(mousePos, _loadButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            loadGame();
            _gameState = GameState::RUNNING;
        }
        if (CheckCollisionPointRec(mousePos, _quitButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT))
        _running = false;
        return;
    }

    if (_raylib->isKeyPressed(KEY_SPACE)) {
        _gameState = (_gameState == GameState::PAUSED) ? GameState::RUNNING : GameState::PAUSED;
    }

    _pauseButtonHovered = CheckCollisionPointRec(mousePos, _pauseButton);
    if (_pauseButtonHovered && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        _gameState = (_gameState == GameState::PAUSED) ? GameState::RUNNING : GameState::PAUSED;
    }

    if (_gameState == GameState::PAUSED) {
        Rectangle resumeBtn = {(float)((1920 - 200) / 2), 480, 200, 60};
        bool resumeHover = CheckCollisionPointRec(mousePos, resumeBtn);
        if (resumeHover && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _gameState = GameState::RUNNING;
            return;
        }

        _pauseSaveButtonHovered = CheckCollisionPointRec(mousePos, _pauseSaveButton);
        if (_pauseSaveButtonHovered && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            saveGame();
            return;
        }

        _pauseQuitButtonHovered = CheckCollisionPointRec(mousePos, _pauseQuitButton);
        if (_pauseQuitButtonHovered && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _running = false;
        }
        return;
    }
    if (CheckCollisionPointRec(mousePos, _clickArea) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        _cycleType == DAY)
    {
        if (policeAlert) {
            _leafs = 0;
        }
        double randomChance = 1 - pow(1 - _tree._leafDropRate, _tree._height);
        double test = (double)rand() / RAND_MAX;
        std::cout << "test and rdc: " << test << randomChance << std::endl;
        _cycleTimer += 0.1f;
        if (test <= randomChance)
        {
            _leafs++;
            _particleSystem.spawn(mousePos, 10);
            triggerShake(5.0f, 0.2f);
            triggerRain(5.0f);
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

    _hoveredShopItem.clear();
    int yPos = 100;
    for (const auto &itemPair : _shop.getObjectList())
    {
        Rectangle itemButton = {_shopArea.x + 20, (float)yPos, _shopArea.width - 40, 50};
        if (CheckCollisionPointRec(mousePos, itemButton) && _cycleType == DUSK) {
            _hoveredShopItem = itemPair.first;
        }
        if (CheckCollisionPointRec(mousePos, itemButton) && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
            _cycleType == DUSK)
        {
            Object boughtObject;
            std::cout << "Trying to buy: " << itemPair.first << std::endl;
            if (_shop.buyObject(itemPair.first, boughtObject, money))
                this->handleBuffing(boughtObject);
        }
        yPos += 60;
    }

    Rectangle sellButton = {_statArea.x + _statArea.width - 220, _statArea.height - 70, 200, 50};
    _sellButtonHovered = CheckCollisionPointRec(mousePos, sellButton) && _cycleType == DUSK && policeAlert == false;
    if (_sellButtonHovered && _raylib->isMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
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
    if (_gameState == GameState::MENU || _gameState == GameState::PAUSED)
        return;
    // if (IsMusicReady(game_music)) {
    //     PlayMusicStream(game_music);
    // } else {
    //     std::cerr << "Failed to load menu music." << std::endl;
    // }
    _timer += dt;
    if (_timer >= 1.0f)
    {
        _cps = _clickCount;
        _clickCount = 0;
        _timer -= 1.0f;
    }
    _cycleTimer += dt;
    _particleSystem.update(dt);
    updateRain(dt);
    if (_shakeTimer > 0) {
        _shakeTimer -= dt;

        float offsetX = (float)GetRandomValue(-_shakeIntensity, _shakeIntensity);
        float offsetY = (float)GetRandomValue(-_shakeIntensity, _shakeIntensity);

        _screenCamera.offset = { offsetX, offsetY };
    } else {
        _screenCamera.offset = { 0.0f, 0.0f };
        _shakeTimer = 0;
    }
    switch (_cycleType)
    {
    case DAY:
        if (_cycleTimer >= 60.0f)
        {
            _cycleType = DUSK;
            _cycleTimer = 0;
            std::cout << "Cycle: Passage au Crepuscule" << std::endl;
        } else {
            int randomPolice = GetRandomValue(0, _tree._height * 2);
            if (randomPolice < (_tree._height - 50) * policeRate) {
                policeAlert = true;
            }
            if (!policeAlert)
            {
                for (Object emp: _employee)
                {
                    double rnd = (double)rand() / RAND_MAX;
                    if (rnd < emp.getBuff())
                    {
                        triggerRain(3.0f);
                        _leafs++;
                    }
                }
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
            int ramdomMalus = GetRandomValue(0, _tree._height * 2);
            if (ramdomMalus < (_tree._height - 25) * malusRate) {
                Malus malus = _malus[rand() % _malus.size()];

                switch (malus.getMalusType())
                {
                case MalusType::LEAF:
                    _leafs -= malus.getPenalty();
                    break;
                case MalusType::MONEY:
                    money -= malus.getPenalty();
                    break;
                case MalusType::TREE:
                    _tree._height -= malus.getPenalty();
                    break;
                default:
                    break;
                }
            }
            for (Object emp: _employee)
            {
                money -= emp.getPrice();
            }
            _cycleType = DAY;
            _cycleTimer = 0;
            dayWeek += 1;
            if (dayWeek >= 7) {
                if (money < debt) {
                    std::cout << "Vous n'avez pas remboursé votre dette! Game Over!" << std::endl;
                    _gameState = GameState::MENU;
                    money = 0;
                    _leafs = 0;
                    debt = 50000;
                    _tree._leafDropRate = 0.01;
                    _tree._height = 1;
                    _employee.clear();
                    dayWeek = 1;
                    policeAlert = false;
                    return;
                } else {
                    money -= debt;
                    std::cout << "Dette remboursée! Argent restant: " << money << " $" << std::endl;
                    debt = rand() % 5000 + (5000 * _tree._height);
                }
                dayWeek = 1;
            }
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
    BeginMode2D(_screenCamera);

    // if (IsMusicReady(game_music)) {
    //     UpdateMusicStream(game_music);
    // }
    if (_gameState == GameState::MENU) {
        drawMenu();
        EndMode2D();
        _raylib->endDrawing();
        return;
    }

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
    Color pauseBtnColor = _pauseButtonHovered ? DARKGRAY : GRAY;
    std::string pauseLabel = (_gameState == GameState::PAUSED) ? "Resume" : "Pause";
    _raylib->drawRectangleRec(_pauseButton, pauseBtnColor);
    int pauseTextWidth = _raylib->measureText(pauseLabel, 20);
    _raylib->drawText(pauseLabel, _pauseButton.x + (_pauseButton.width - pauseTextWidth) / 2, _pauseButton.y + 10, 20, BLACK);

    _raylib->drawText("Shop", _shopArea.x + (_shopArea.width - _raylib->measureText("Shop", 40)) / 2, 20, 40, BLACK);
    Color textColor = (_cycleType == NIGHT) ? WHITE : BLACK;
    _raylib->drawText("Click Here", _clickArea.x + (_clickArea.width - _raylib->measureText("Click Here", 40)) / 2, 20,
                      40, textColor);
    _raylib->drawText("Stat", _statArea.x + (_statArea.width - _raylib->measureText("Stat", 40)) / 2, 20, 40, BLACK);
    Rectangle treeRect = {0, 0, 1000, 3240/3};
    Vector2 treePos = {460, 10};
    if (_tree._height > 100) {
        treeRect.y = 3240/3*2;
    } else if (_tree._height > 50) {
        treeRect.y = 3240/3;
    }
    _raylib->drawTextureRect("tree", treeRect, treePos, WHITE);

    drawStats();
    drawShop();

    Rectangle sellButton = {_statArea.x + _statArea.width - 220, _statArea.height - 70, 200, 50};
    Color buttonColor = GRAY;
    if (_cycleType == DUSK && policeAlert == false) {
        buttonColor = (_leafs > 0) ? LIME : GRAY;
        if (_sellButtonHovered && _leafs > 0) buttonColor = GREEN;
    }
    _raylib->drawRectangleRec(sellButton, buttonColor);
    std::string sellText = "Vendre Feuille (100)";
    int textWidth = _raylib->measureText(sellText, 20);
    _raylib->drawText(sellText, sellButton.x + (sellButton.width - textWidth) / 2, sellButton.y + 15, 20, BLACK);
    _particleSystem.draw();
    drawRain();
    EndMode2D();

    if (_gameState == GameState::PAUSED) {
        drawPauseOverlay();
    }
    if (_gameState != GameState::MENU) _raylib->endDrawing();
}

void Game::drawShop()
{
    int yPos = 100;
    int fontSize = 20;
    for (const auto &itemPair : _shop.getObjectList())
    {
        Rectangle itemButton = {_shopArea.x + 20, (float)yPos, _shopArea.width - 40, 50};
        Color buttonColor = LIGHTGRAY;
        if (_cycleType == DUSK && itemPair.first == _hoveredShopItem) {
            buttonColor = GRAY;
        }
        _raylib->drawRectangleRec(itemButton, buttonColor);
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
    stats.push_back("Debt: " + std::to_string(debt) + " $");
    stats.push_back("Day: " + std::to_string(dayWeek));
    stats.push_back("Leaf: " + std::to_string(_leafs));
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

void Game::drawPauseOverlay()
{
    DrawRectangle(0, 0, 1920, 1080, Fade(BLACK, 0.5f));
    std::string pausedText = "PAUSE";
    int fontSize = 80;
    int textWidth = _raylib->measureText(pausedText, fontSize);
    _raylib->drawText(pausedText, (1920 - textWidth) / 2, 400, fontSize, WHITE);

    auto drawButton = [&](const Rectangle &rect, const std::string &label, bool hovered) {
        Color buttonColor = hovered ? LIME : LIGHTGRAY;
        _raylib->drawRectangleRec(rect, buttonColor);
        int btnTextWidth = _raylib->measureText(label, 28);
        _raylib->drawText(label, rect.x + (rect.width - btnTextWidth) / 2, rect.y + 16, 28, BLACK);
    };

    Rectangle resumeBtn = {(float)((1920 - 200) / 2), 480, 200, 60};
    bool resumeHover = CheckCollisionPointRec(_raylib->getMousePosition(), resumeBtn);
    drawButton(resumeBtn, "Reprendre", resumeHover);
    drawButton(_pauseSaveButton, "Sauvegarder", _pauseSaveButtonHovered);
    drawButton(_pauseQuitButton, "Quitter", _pauseQuitButtonHovered);
}

void Game::drawMenu()
{
    Vector2 mousePos = _raylib->getMousePosition();

    std::string title = "GrosAZ";
    int titleSize = 80;
    int titlePosX = (1920 - _raylib->measureText(title, titleSize)) / 2;
    _raylib->drawText(title, titlePosX, 180, titleSize, DARKGREEN);

    // UpdateMusicStream(menu_music);
    auto drawButton = [&](const Rectangle &rect, const std::string &label) {
        bool hovered = CheckCollisionPointRec(mousePos, rect);
        Color buttonColor = hovered ? LIME : LIGHTGRAY;
        _raylib->drawRectangleRec(rect, buttonColor);
        int textWidth = _raylib->measureText(label, 30);
        _raylib->drawText(label, rect.x + (rect.width - textWidth) / 2, rect.y + 25, 30, BLACK);
    };

    drawButton(_playButton, "Jouer");
    drawButton(_loadButton, "Charger");
    drawButton(_quitButton, "Quitter");
}

void Game::triggerShake(float intensity, float duration)
{
    _shakeIntensity = intensity; // Force du tremblement en pixels (ex: 5.0f)
    _shakeTimer = duration;      // Durée en secondes (ex: 0.2f)
}

void Game::saveGame(const std::string &filePath) const
{
    SaveData data{};
    data.money = money;
    data.leafs = _leafs;
    data.debt = debt;
    data.dayWeek = dayWeek;
    data.malusRate = malusRate;
    data.clientRate = clientRate;
    data.policeRate = policeRate;
    data.treeHeight = _tree._height;
    data.leafDropRate = _tree._leafDropRate;
    data.cycleType = static_cast<int>(_cycleType);
    data.cycleTimer = _cycleTimer;
    data.policeAlert = policeAlert;

    std::ofstream out(filePath);
    if (!out) {
        std::cerr << "Failed to open save file: " << filePath << std::endl;
        return;
    }
    out << data.money << "\n"
        << data.leafs << "\n"
        << data.debt << "\n"
        << data.dayWeek << "\n"
        << data.malusRate << "\n"
        << data.clientRate << "\n"
        << data.policeRate << "\n"
        << data.treeHeight << "\n"
        << data.leafDropRate << "\n"
        << data.cycleType << "\n"
        << data.cycleTimer << "\n"
        << data.policeAlert << "\n";
    std::cout << "Game saved to " << filePath << " (text)" << std::endl;
}

void Game::loadGame(const std::string &filePath)
{
    SaveData data{};
    std::ifstream in(filePath);
    if (!in) {
        std::cerr << "Save file not found: " << filePath << std::endl;
        return;
    }
    in >> data.money
        >> data.leafs
        >> data.debt
        >> data.dayWeek
        >> data.malusRate
        >> data.clientRate
        >> data.policeRate
        >> data.treeHeight
        >> data.leafDropRate
        >> data.cycleType
        >> data.cycleTimer
        >> data.policeAlert;
    if (!in) {
        std::cerr << "Failed to read save file: " << filePath << std::endl;
        return;
    }

    money = data.money;
    _leafs = data.leafs;
    debt = data.debt;
    dayWeek = data.dayWeek;
    malusRate = data.malusRate;
    clientRate = data.clientRate;
    policeRate = data.policeRate;
    _tree._height = data.treeHeight;
    _tree._leafDropRate = data.leafDropRate;
    _cycleType = static_cast<CycleType>(data.cycleType);
    _cycleTimer = data.cycleTimer;
    policeAlert = data.policeAlert;

    std::cout << "Game loaded from " << filePath << " (text)" << std::endl;
}

void Game::triggerRain(float durationSeconds)
{
    _rainDuration = durationSeconds;
    _rainTimer = 0.0f;
    if (_isRaining == true)
        return;
    _isRaining = true;

    for (auto &leaf : _rainLeaves) {
        leaf.pos.x = (float)(rand() % 1920); // Largeur écran
        leaf.pos.y = (float)(rand() % 1080 - 1080); // Position aléatoire au-dessus
        leaf.speed = 200.0f + (rand() % 300); // Vitesse entre 200 et 500
    }
    std::cout << "Pluie déclenchée pour " << durationSeconds << " secondes !" << std::endl;
}

void Game::updateRain(float dt)
{
    // Si la pluie n'est pas active et que le timer est fini, on ne fait rien
    if (!_isRaining) return;

    _rainTimer += dt;

    // Vérifie si le temps de pluie est écoulé
    bool timeIsUp = _rainTimer >= _rainDuration;
    bool visibleLeafFound = false;

    for (auto &leaf : _rainLeaves) {
        leaf.pos.y += leaf.speed * dt;

        // Si la feuille sort en bas de l'écran (1080)
        if (leaf.pos.y > 1080) {
            if (!timeIsUp) {
                // S'il reste du temps : on recycle la feuille en haut
                leaf.pos.y = -50; 
                leaf.pos.x = (float)(rand() % 1920);
                visibleLeafFound = true;
            }
            // Sinon (timeIsUp), on ne la remonte pas, on la laisse tomber dans le vide
        } else {
            // La feuille est encore sur l'écran
            visibleLeafFound = true;
        }
    }

    // Si le temps est écoulé ET qu'il n'y a plus aucune feuille visible, on arrête tout
    if (timeIsUp && !visibleLeafFound) {
        _isRaining = false;
        std::cout << "Fin de la pluie." << std::endl;
    }
}

void Game::drawRain()
{
    if (!_isRaining) return;

    // 1. Source : On prend TOUT le sprite (width/height de la texture originale)
    Rectangle source = { 0.0f, 0.0f, (float)_leafTexture.width, (float)_leafTexture.height };

    // 2. Origine de rotation (coin haut gauche ici)
    Vector2 origin = { 0.0f, 0.0f };

    for (const auto &leaf : _rainLeaves) {
        // On ne dessine que si c'est visible (petite optimisation)
        if (leaf.pos.y > -50 && leaf.pos.y < 1080) {
            
            // 3. Destination : On force la taille à 25x25 à la position de la feuille
            Rectangle dest = { leaf.pos.x, leaf.pos.y, 25.0f, 25.0f };
            
            // Utilisation de DrawTexturePro (Raylib standard) pour le scaling précis
            DrawTexturePro(_leafTexture, source, dest, origin, 0.0f, WHITE);
        }
    }
}