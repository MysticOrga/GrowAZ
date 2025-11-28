/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Raylib/Raylib.hpp"
#include <memory>

class Game {
    public:
        Game();
        ~Game();
        void run();

    protected:
    private:
        void handleEvents();
        void update();
        void draw();

        std::unique_ptr<Raylib> _raylib;
        long long _score;
};

#endif /* !GAME_HPP_ */
