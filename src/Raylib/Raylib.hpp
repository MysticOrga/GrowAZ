/*
** EPITECH PROJECT, 2024
** GrosAZ
** File description:
** Raylib
*/

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

#include <raylib.h>
#include <string>
#include <vector>
#include <map>

class Raylib {
    public:
        Raylib(int screenWidth, int screenHeight, const std::string &title);
        ~Raylib();

        // Window management
        bool windowShouldClose() const;
        void beginDrawing();
        void endDrawing();
        void clearBackground(Color color);
        float getFrameTime() const;

        // Texture/Sprite management
        void loadTexture(const std::string &name, const std::string &fileName);
        void drawTexture(const std::string &name, int posX, int posY, Color tint = WHITE);
        void drawTextureV(const std::string& name, Vector2 position, Color tint = WHITE);
        Texture2D getTexture(const std::string &name);
        void unloadTexture(const std::string &name);

        // Mouse events
        bool isMouseButtonPressed(int button) const;
        bool isMouseButtonDown(int button) const;
        bool isMouseButtonReleased(int button) const;
        Vector2 getMousePosition() const;
        bool isKeyPressed(int key) const;

        // Sound management
        void loadSound(const std::string &name, const std::string &fileName);
        void playSound(const std::string &name);
        void unloadSound(const std::string &name);
        void setSoundVolume(const std::string& name, float volume);

        //Draw Text
        void drawText(const std::string &text, int posX, int posY, int fontSize, Color color);
        void drawRectangleRec(Rectangle rec, Color color);
        int measureText(const std::string &text, int fontSize);

    protected:
    private:
        std::map<std::string, Texture2D> _textures;
        std::map<std::string, Sound> _sounds;
};

#endif /* !RAYLIB_HPP_ */
