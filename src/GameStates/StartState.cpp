//
// Created by Joste on 05.04.2021.
//

#include <memory>
#include <iostream>
#include "../../include/GameStates/StartState.h"
#include "../../include/GameManager.h"


StartState::StartState() {
    snakeText = std::make_unique<GameObject>(208,304,384,192);
    snakeBackground = std::make_unique<GameObject>(0,0,800,800);
    playGameText = std::make_unique<GameObject>(208,500,384,80);

    snakeText->texture = TextureManager::GetInstance().LoadTexture("../images/SnakeTextStartScreen.png");
    snakeBackground->texture = TextureManager::GetInstance().LoadTexture("../images/SnakeStartBackground.png");
    playGameText->texture = TextureManager::GetInstance().LoadTexture("../images/PlayGameText.png"); // TODO Bytt til ttf text
}

void StartState::Render() {
    snakeBackground->Render();
    snakeText->Render();
    playGameText->Render();
}

void StartState::HandleInputs() {
    if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1))){
        std::cout << "Switching state to main screen" << std::endl;
        GameManager::GetInstance().SwitchToNextState();
    }
}
