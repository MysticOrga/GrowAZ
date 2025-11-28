#pragma once

#include "raylib.h"
#include <algorithm>
#include <string>
#include <vector>

struct FloatingText
{
    Vector2 position;
    float alpha;
    float lifetime;
    std::string text;
};

class FloatingTextManager {
    public:
        void spawn(const Vector2 &pos, const std::string &text);
        void update(float dt);
        void draw() const;
    private:
        std::vector<FloatingText> texts;
};
