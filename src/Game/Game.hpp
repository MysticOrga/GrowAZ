#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Raylib/Raylib.hpp"
#include <memory>
#include <cstdlib>

class Tree
{
  public:
    Tree() : _height(0), _leafDropRate(0.05) {};
    ~Tree() = default;
    long long _height;
    double _leafDropRate;

  private:
};

class Game
{
  public:
    Game();
    ~Game();
    void run();

  protected:
  private:
    void handleEvents();
    void update();
    void draw();
    void drawStats();

    Tree _tree; // <--- AJOUTE CECI : L'instance de l'arbre

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
    float _timer;
};

#endif /* !GAME_HPP_ */