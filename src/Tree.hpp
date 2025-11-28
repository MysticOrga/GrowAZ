#pragma once

#include "raylib.h"

class Tree {
    public:
        Tree(Vector2 center, float foliageRadius, float trunkWidth, float trunkHeight);

        void draw();
        void animate(float dt);
        bool contains(const Vector2 &point);
        void popFoliage();

    private:
        Rectangle getTrunkRect();
        bool isOnFoliage(const Vector2 &point);

        Vector2 position;
        float foliageRadius;
        float trunkWidth;
        float trunkHeight;
        float foliageScale;
};
