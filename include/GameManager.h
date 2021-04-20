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
#include "AudioManager.h"


constexpr SDL_Color BLACK_COLOR = {0, 0, 0, 0}; // Plasser disse i stateinterface?
constexpr SDL_Color WHITE_COLOR = {255, 255, 255, 255};
constexpr SDL_Color GREEN_COLOR = {0, 255, 0, 255};
constexpr SDL_Color RED_COLOR = {255, 0, 0};

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

    SDL_Renderer *renderer;

    bool gameRunning;

    int frameCounter;

    void SwitchToNextState();

    GameManager();
private:
    ~GameManager();

    void Update();

    void Render() const;

    void DestroySDLObjects();

    SDL_Window *window;

    int state;

    std::chrono::time_point<std::chrono::high_resolution_clock> currentTimeFrame;
};

#endif //SNAKE_GAMEMANAGER_H
