//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../include/GameManager.h"


void GameManager::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Gamehandler Initialised!" << std::endl;

        window = SDL_CreateWindow(
                "Snake",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                800,
                800,
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }else{
        gameRunning = false;
    }
    TextureManager::GetInstance().ReadTexturesFromFile();
    TTF_Init();
    FontManager::GetInstance().SetFont();
}

void GameManager::Render() const {
    switch(state){
        case 0:
            StartState::GetInstance().Render();
            StartState::GetInstance().HandleInputs();
            break;
        case 1:
            MainState::GetInstance().Render();
            MainState::GetInstance().Update();
            break;
        case 2:
            EndState::GetInstance().HandleInputs();
            EndState::GetInstance().Render();
            break;
        default:
            break;
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void GameManager::DestroySDLObjects(){
    std::cout << "Cleaning up the game."<< std::endl;
    AudioManager::GetInstance().CleanAudio();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}


void GameManager::Update(){
    InputManager::GetInstance().Update();
    if(InputManager::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE) || SDL_HasEvent(SDL_QUIT)){
        gameRunning = false;
    }
}

GameManager::~GameManager() {
    DestroySDLObjects();
}

GameManager::GameManager() :
    gameRunning(true),
    state(0),
    frameCounter(0),
    window(nullptr),
    renderer(nullptr)
    {

}

void GameManager::GameLoop() {
    currentTimeFrame = std::chrono::high_resolution_clock::now(); // static?

    using namespace std::chrono_literals;
    while(gameRunning){
        auto lastFrame = currentTimeFrame;
        currentTimeFrame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> deltaTimeMs = currentTimeFrame - lastFrame;
        if((20ms - deltaTimeMs) > std::chrono::duration<float, std::milli>(0)){
            std::this_thread::sleep_for(20ms - deltaTimeMs);
        }
        Render();
        Update();
        frameCounter++;
    }
}

void GameManager::SwitchToNextState() {
    if(state < 2)
        state++;
    else
        state--;
}
