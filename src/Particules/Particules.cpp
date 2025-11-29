/*
** EPITECH PROJECT, 2025
** GrosAZ
** File description:
** Particules
*/

#include "Particules.hpp"
#include <cstdlib>

ParticleSystem::ParticleSystem() : _poolIndex(0) {}

ParticleSystem::~ParticleSystem() {}

void ParticleSystem::init(int maxParticles) {
    _pool.resize(maxParticles);
    for (auto& p : _pool) {
        p.active = false;
    }
}

void ParticleSystem::spawn(Vector2 position, int amount) {
    int spawnedCount = 0;

    for (int i = 0; i < _pool.size(); i++) {
        int idx = (_poolIndex + i) % _pool.size(); 

        if (!_pool[idx].active) {
            Particle& p = _pool[idx];
            p.active = true;
            p.position = position;

            float angle = (float)GetRandomValue(0, 360) * (PI / 180.0f);
            // Vitesse aléatoire
            float speed = (float)GetRandomValue(100, 300); 
            
            p.velocity = { (float)cos(angle) * speed, (float)sin(angle) * speed };
            
            // --- COULEUR VERTE ---
            // On fait varier le vert entre 150 et 255 pour du relief
            unsigned char valGreen = (unsigned char)GetRandomValue(150, 255);
            // R=0, G=Variable, B=0 => Vert pur
            p.color = { 0, valGreen, 20, 255 }; 

            p.size = (float)GetRandomValue(4, 8);
            p.maxLife = (float)GetRandomValue(5, 12) / 10.0f; // 0.5 à 1.2 secondes
            p.life = p.maxLife;

            spawnedCount++;
            if (spawnedCount >= amount) {
                _poolIndex = idx + 1; // On retient où on s'est arrêté
                break;
            }
        }
    }
}

void ParticleSystem::update(float dt) {
    for (auto& p : _pool) {
        if (!p.active) continue;

        // Mouvement
        p.position.x += p.velocity.x * dt;
        p.position.y += p.velocity.y * dt;

        // Gravité (les feuilles tombent)
        p.velocity.y += 400.0f * dt; 

        // Vieillissement
        p.life -= dt;

        // Gestion de la transparence (Alpha)
        float alpha = p.life / p.maxLife;
        if (alpha < 0) alpha = 0;
        p.color.a = (unsigned char)(alpha * 255);

        // Mort
        if (p.life <= 0) {
            p.active = false;
        }
    }
}

void ParticleSystem::draw() {
    for (const auto& p : _pool) {
        if (p.active) {
            DrawCircle((int)p.position.x, (int)p.position.y, p.size, p.color);
            // Si tu veux des carrés : DrawRectangle(...)
        }
    }
}