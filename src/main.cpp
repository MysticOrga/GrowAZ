/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** main
*/

#include "Game/Game.hpp"
#include <iostream>

int main(void)
{
    try {
        Game game;
        game.run();
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}