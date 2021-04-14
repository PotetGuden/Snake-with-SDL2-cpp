//
// Created by Joste on 05.04.2021.
//

#include <memory>
#include <iostream>
#include "../../include/GameStates/StartState.h"
#include "../../include/GameManager.h"

void StartState::Render() {
    snakeBackground->Render();
    snakeText->Render();
    playGameText->Render();
}

StartState::StartState() {
    snakeText = std::make_unique<GameObject>(208,304,384,192);
    snakeBackground = std::make_unique<GameObject>(0,0,800,800);
    playGameText = std::make_unique<GameObject>(208,500,384,80);

    snakeText->texture = TextureManager::LoadTexture("../images/SnakeTextStartScreen.png");
    snakeBackground->texture = TextureManager::LoadTexture("../images/SnakeStartBackground.png");
    playGameText->texture = TextureManager::LoadTexture("../images/PlayGameText.png"); // TODO Bytt til ttf text
}
