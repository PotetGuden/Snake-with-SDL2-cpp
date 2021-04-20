//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../include/GameManager.h"


// .reset() shared_ptr

//SDL_Renderer *GameManager::renderer = nullptr;


// TODO sette variabler med function() : variabelNavn(name)
// TODO pass by value i funksjoner "&"
// TODO FIKS FRUIT ON FRUIT??
// TODO Bytt om alle LoadTexture -> LoadTextures for å få de inn i map
// TODO Minnelekssje mest sansynlig textures (kaaanskje audio)

void GameManager::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){ // Tar med lyd/audio
        std::cout << "Gamehandler Initialised!" << std::endl;

        window = SDL_CreateWindow(
                "Snake",                      //    window title
                SDL_WINDOWPOS_UNDEFINED,                //    initial x position
                SDL_WINDOWPOS_UNDEFINED,                //    initial y position
                800,                                    //    width, in pixels
                800,                                    //    height, in pixels
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL  //    flags

        );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        gameRunning = true;
    }else{
        gameRunning = false;
    }

    TextureManager::GetInstance().ReadTexturesFromFile();

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
    std::cout << "Cleaning up the game window."<< std::endl;
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
    TTF_Init();
    FontManager::GetInstance().SetFont();
}

void GameManager::GameLoop() {
    currentTimeFrame = std::chrono::high_resolution_clock::now(); // static?
    //frameCounter = 0;

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
