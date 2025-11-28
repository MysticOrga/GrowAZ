#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Raylib/Raylib.hpp"
#include <memory>
#include <cstdlib>
#include <vector> // Nécessaire pour std::vector dans drawStats

enum CycleType {
    DAY,
    DUSK,  // Crépuscule
    NIGHT
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

    Tree _tree;

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
    double _cps;
    int _clickCount;
    
    // Timers
    float _timer;       // Timer pour le CPS (reset chaque 1s)
    float _cycleTimer;  // Timer pour le Cycle (Jour/Nuit)

    CycleType _cycleType;
};

#endif /* !GAME_HPP_ */