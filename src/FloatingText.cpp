#include "FloatingText.hpp"

void FloatingTextManager::spawn(const Vector2 &pos, const std::string &text)
{
    texts.push_back(FloatingText{
        .position = pos,
        .alpha = 1.0f,
        .lifetime = 1.0f,
        .text = text});
}

void FloatingTextManager::update(float dt)
{
    for (auto &txt : texts) {
        txt.position.y -= 60.0f * dt;
        txt.alpha -= 1.2f * dt;
        txt.lifetime -= dt;
    }
    texts.erase(
        std::remove_if(texts.begin(), texts.end(), [](const FloatingText &t) { return t.alpha <= 0.0f || t.lifetime <= 0.0f; }),
        texts.end());
}

void FloatingTextManager::draw() const
{
    for (const auto &txt : texts) {
        unsigned char a = static_cast<unsigned char>(std::clamp(txt.alpha, 0.0f, 1.0f) * 255);
        DrawText(txt.text.c_str(), static_cast<int>(txt.position.x), static_cast<int>(txt.position.y), 24, {255, 0, 0, a});
    }
}
