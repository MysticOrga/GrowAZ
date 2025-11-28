/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Raylib
*/

#include "Raylib.hpp"

Raylib::Raylib(int screenWidth, int screenHeight, const std::string &title)
{
    InitWindow(screenWidth, screenHeight, title.c_str());
    InitAudioDevice();
    SetTargetFPS(60);
}

Raylib::~Raylib()
{
    for (auto const& [name, texture] : _textures) {
        (void)name; // Unused
        UnloadTexture(texture);
    }
    _textures.clear();

    for (auto const& [name, sound] : _sounds) {
        (void)name; // Unused
        UnloadSound(sound);
    }
    _sounds.clear();

    CloseAudioDevice();
    CloseWindow();
}

bool Raylib::windowShouldClose() const
{
    return WindowShouldClose();
}

void Raylib::beginDrawing()
{
    BeginDrawing();
}

void Raylib::endDrawing()
{
    EndDrawing();
}

void Raylib::clearBackground(Color color)
{
    ClearBackground(color);
}

void Raylib::loadTexture(const std::string &name, const std::string &fileName)
{
    if (_textures.find(name) != _textures.end()) {
        return;
    }
    _textures[name] = LoadTexture(fileName.c_str());
}

void Raylib::drawTexture(const std::string &name, int posX, int posY, Color tint)
{
    if (_textures.find(name) == _textures.end()) {
        // Maybe log an error, for now, just return.
        return;
    }
    DrawTexture(_textures[name], posX, posY, tint);
}

void Raylib::drawTextureV(const std::string& name, Vector2 position, Color tint)
{
    if (_textures.find(name) == _textures.end()) {
        return;
    }
    DrawTextureV(_textures[name], position, tint);
}

Texture2D Raylib::getTexture(const std::string &name)
{
    if (_textures.find(name) == _textures.end()) {
        return Texture2D{};
    }
    return _textures[name];
}

void Raylib::unloadTexture(const std::string &name)
{
    if (_textures.find(name) != _textures.end()) {
        UnloadTexture(_textures[name]);
        _textures.erase(name);
    }
}

bool Raylib::isMouseButtonPressed(int button) const
{
    return IsMouseButtonPressed(button);
}

bool Raylib::isMouseButtonDown(int button) const
{
    return IsMouseButtonDown(button);
}

bool Raylib::isMouseButtonReleased(int button) const
{
    return IsMouseButtonReleased(button);
}

Vector2 Raylib::getMousePosition() const
{
    return GetMousePosition();
}

void Raylib::loadSound(const std::string &name, const std::string &fileName)
{
    if (_sounds.find(name) != _sounds.end()) {
        return;
    }
    _sounds[name] = LoadSound(fileName.c_str());
}

void Raylib::playSound(const std::string &name)
{
    if (_sounds.find(name) == _sounds.end()) {
        return;
    }
    PlaySound(_sounds[name]);
}

void Raylib::unloadSound(const std::string &name)
{
    if (_sounds.find(name) != _sounds.end()) {
        UnloadSound(_sounds[name]);
        _sounds.erase(name);
    }
}

void Raylib::setSoundVolume(const std::string& name, float volume)
{
    if (_sounds.find(name) == _sounds.end()) {
        return;
    }
    SetSoundVolume(_sounds[name], volume);
}

void Raylib::drawText(const std::string &text, int posX, int posY, int fontSize, Color color)
{
    DrawText(text.c_str(), posX, posY, fontSize, color);
}