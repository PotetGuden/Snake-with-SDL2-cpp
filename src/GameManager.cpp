//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include "../include/GameManager.h"
#include "../include/AudioManager.h"

// .reset() shared_ptr

SDL_Renderer *GameManager::renderer = nullptr;

// TODO const etter funksjonsnavn?
// TODO sdl_destroy texture
// TODO sette alle funksjoner/variabler som private om mulig (bare de som ikke blir kalt fra andre klasser)
// TODO lage loops for å emplace_back() fruits
// TODO sette variabler med function() : variabelNavn(name)
// TODO pass by value i funksjoner "&"
// TODO Loade alle textures i gamemanager for å destroye de i construcor??
// TODO FIKS FRUIT ON FRUIT??
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
}

void GameManager::Render() {
    /*if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1))){
        std::cout << "Switching state to end screen" << std::endl;
        state = 1;
    }*/
    /*if(InputManager::GetInstance().MouseDown(SDL_BUTTON(3))){
        std::cout << "Switching state to end screen" << std::endl;
        state = 2;
    }*/

    switch(state){
        case 0:
            StartState::GetInstance().Render();
            StartState::GetInstance().HandleInputs();
            break;
        case 1:
            //mainScreen->Render();
            //mainScreen->Update();
            MainState::GetInstance().Render();
            MainState::GetInstance().Update();
            break;
        case 2:
            //endScreen->Render();
            EndState::GetInstance().Render();
            EndState::GetInstance().HandleInputs();
            break;
        default:
            break;
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void GameManager::DestroySDLObjects(){
    std::cout << "Cleaning up the game window."<< std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    AudioManager::GetInstance().CleanAudio();

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}


void GameManager::Update(){
    InputManager::GetInstance().Update();
    if(InputManager::GetInstance().KeyDown(SDL_SCANCODE_ESCAPE) || SDL_HasEvent(SDL_QUIT)){
        GameManager::GetInstance().gameRunning = false;
    }
    //mainScreen->Update();
}

GameManager::~GameManager() {
    DestroySDLObjects();
}

GameManager::GameManager(){
    state = 0;
    TTF_Init();

}

void GameManager::GameLoop() {
    currentTimeFrame = std::chrono::high_resolution_clock::now(); // static?
    frameCounter = 0;

    while(gameRunning){
        using namespace std::chrono_literals;
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

    // state = (state < 3) ? state++ : state-- ; hør med kjetil
}
