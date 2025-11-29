#ifndef GAME_HPP_
#define GAME_HPP_

#include "../Raylib/Raylib.hpp"
#include <memory>
#include <cstdlib>
#include <vector> // Nécessaire pour std::vector dans drawStats
#include <fstream>
#include "./Object/Shop.hpp"
#include "./Object/Object.hpp"
#include "./Malus/Malus.hpp"
#include "./Particules/Particules.hpp"

enum CycleType {
    DAY,
    DUSK,  // Crépuscule
    NIGHT
};

enum class GameState {
    MENU,
    RUNNING,
    PAUSED
};

class Tree
{
  public:
    Tree() : _height(0), _leafDropRate(0.05) {};
    ~Tree() = default;
    long long _height;
    double _leafDropRate;
};

struct FallingLeaf {
    Vector2 pos;
    float speed;
};

struct SaveData {
    long long money;
    long long leafs;
    long long debt;
    int dayWeek;
    double malusRate;
    double clientRate;
    double policeRate;
    long long treeHeight;
    double leafDropRate;
    int cycleType;
    float cycleTimer;
    bool policeAlert;
};

class Game
{
  public:
    Game();
    ~Game();
    void run();

  private:
    void handleEvents();
    void update();
    void draw();
    void drawStats();
    void drawShop();
    void drawMenu();
    void drawPauseOverlay();
    void handleBuffing(const Object obj);
    void triggerShake(float intensity, float duration);
    void saveGame(const std::string &filePath = "save.txt") const;
    void loadGame(const std::string &filePath = "save.txt");
    void triggerRain(float durationSeconds);
    void updateRain(float dt);
    void drawRain();

    std::vector<FallingLeaf> _rainLeaves;
    float _rainDuration;    // Combien de temps la pluie doit durer
    float _rainTimer;       // Compteur de temps actuel
    float _groundTimer;
    bool _isRaining;        // Est-ce que la pluie est active ?
    Texture2D _leafTexture;
    Rectangle _groundRect;
    Tree _tree;
    Shop _shop;
    std::vector<Malus> _malus;
    std::vector<Object> _employee;

    /* Rates */
    double malusRate;
    double clientRate;
    double policeRate;

    long long money;
    std::unique_ptr<Raylib> _raylib;
    long long _leafs;
    Rectangle _shopArea;
    Rectangle _clickArea;
    Rectangle _statArea;

    Rectangle _playButton;
    Rectangle _loadButton;
    Rectangle _quitButton;
    Rectangle _pauseButton;
    Rectangle _pauseSaveButton;
    Rectangle _pauseQuitButton;
    bool _running;
    GameState _gameState;

    double _cps;
    int _clickCount;
    bool policeAlert;
    long long debt;
    int dayWeek;

    float _timer;
    float _cycleTimer;

    CycleType _cycleType;

    std::string _hoveredShopItem;
    bool _sellButtonHovered;

    ParticleSystem _particleSystem;
    bool _pauseButtonHovered;
    bool _pauseSaveButtonHovered;
    bool _pauseQuitButtonHovered;

    Camera2D _screenCamera;
    float _shakeTimer;
    float _shakeIntensity;

    Music menu_music;
    Music game_music;
};

#endif /* !GAME_HPP_ */
