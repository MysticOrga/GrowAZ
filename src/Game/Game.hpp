#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Raylib/Raylib.hpp"
#include <memory>
#include <cstdlib>
#include <vector> // Nécessaire pour std::vector dans drawStats
#include "./Object/Shop.hpp"
#include "./Object/Object.hpp"
#include "./Malus/Malus.hpp"

enum CycleType {
    DAY,
    DUSK,  // Crépuscule
    NIGHT
};

enum class GameState {
    MENU,
    RUNNING,
    PAUSED
};

class Tree
{
  public:
    Tree() : _height(0), _leafDropRate(0.05) {};
    ~Tree() = default;
    long long _height;
    double _leafDropRate;
};

class Game
{
  public:
    Game();
    ~Game();
    void run();

  private:
    void handleEvents();
    void update();
    void draw();
    void drawStats();
    void drawShop();
    void drawMenu();
    void drawPauseOverlay();
    void handleBuffing(const Object obj);

    Tree _tree;
    Shop _shop;
    std::vector<Malus> _malus;

    /* Rates */
    double malusRate;
    double clientRate;
    double policeRate;

    long long money;
    std::unique_ptr<Raylib> _raylib;
    long long _leafs;
    Rectangle _shopArea;
    Rectangle _clickArea;
    Rectangle _statArea;

    Rectangle _playButton;
    Rectangle _quitButton;
    Rectangle _pauseButton;
    Rectangle _pauseQuitButton;
    bool _running;
    GameState _gameState;

    double _cps;
    int _clickCount;
    bool policeAlert;
    long long debt;
    int dayWeek;

    float _timer;
    float _cycleTimer;

    CycleType _cycleType;

    std::string _hoveredShopItem;
    bool _sellButtonHovered;
    bool _pauseButtonHovered;
    bool _pauseQuitButtonHovered;
};

#endif /* !GAME_HPP_ */
