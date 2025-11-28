#pragma once

#include "FloatingText.hpp"
#include "Tree.hpp"
#include <random>
#include <string>

class Game
{
public:
    Game(int width, int height);
    void run();

private:
    void handleInput();
    void update(float dt);
    void draw();
    void drawUI();
    bool rollDrop();

    int screenWidth;
    int screenHeight;
    Tree tree;
    FloatingTextManager floatingTexts;
    int leaves = 0;

    std::mt19937 rng; //mt19937 c'est un générateur de nombres aléatoires opti pour la rng askip
    std::uniform_real_distribution<float> dropDist; //Transforme les nombres du générateur pour qu'ils suivent une disbutions uniforme (chaque val d'une intervalle a la meme chance d'etre tirer)
};
