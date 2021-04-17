//
// Created by Joste on 26.03.2021.
//

#ifndef SNAKE_GAMEMANAGER_H
#define SNAKE_GAMEMANAGER_H


#include <SDL.h>
#include <vector>
#include <chrono>
#include <thread>

#include "InputManager.h"
#include "Snake.h"
#include "Fruit.h"
#include "FontManager.h"
#include "ScoreManager.h"
#include "GameStates/StartState.h"
#include "GameStates/MainState.h"
#include "GameStates/EndState.h"

//#define BLOCK_SIZE 32  // width and height of each tile, wall, fruit and snake part
//constexpr int BLOCK_SIZE = 32; // Modern c++ instead of #define
constexpr int BLOCK_WIDTH = 32; // Modern c++ instead of #define
constexpr int BLOCK_HEIGHT = 32; // Modern c++ instead of #define
constexpr int HEADER_Y_OFFSET = 160; // Modern c++ instead of #define


class GameManager {
public:

    static GameManager &GetInstance(){
        static GameManager instance;
        return instance;
    }
    GameManager(GameManager const &) = delete;     // Copy Constructor
    GameManager(GameManager const &&) = delete;    // Move Constructor
    void operator = (GameManager const&) = delete;  // Likhetsoperator

    void Init();
    void GameLoop();

    static SDL_Renderer *renderer;

    bool gameRunning;
    int frameCounter;

    void SwitchToNextState();

    GameManager();
private:
    ~GameManager();

    void Update();
    void Render();
    void DestroySDLObjects();

    SDL_Window *window;
    int state;
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTimeFrame;
};
#endif //SNAKE_GAMEMANAGER_H
