/*
** EPITECH PROJECT, 2025
** GrosAZ
** File description:
** Particules
*/

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include "../Raylib/Raylib.hpp"
#include <vector>
#include <cmath>

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float life;
    float maxLife;
    bool active;
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    // Appelle ça une seule fois au début
    void init(int maxParticles = 1000);

    // Appelle ça pour créer une explosion à une position donnée
    void spawn(Vector2 position, int amount = 10);

    // Appelle ça dans ton Game::update
    void update(float dt);

    // Appelle ça dans ton Game::draw
    void draw();

private:
    std::vector<Particle> _pool;
    int _poolIndex; // Pour optimiser la recherche de particules libres
};

#endif