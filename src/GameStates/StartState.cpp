//
// Created by Joste on 05.04.2021.
//

#include <memory>
#include <iostream>
#include "../../include/GameStates/StartState.h"
#include "../../include/GameManager.h"
constexpr SDL_Color BLACK_COLOR = {0, 0, 0, 0};

StartState::StartState() {
    snakeText = std::make_unique<GameObject>(208,304,384,192);
    snakeBackground = std::make_unique<GameObject>(0,0,800,800);
    playGameText = std::make_unique<GameObject>(208,500,384,80);

    //std::string yolo = "PlayGameBackground";
    //std::string yolo2 = "../images/game-states/start/PlayGameText.png";
    //TextureManager::GetInstance().LoadTextures(yolo, yolo2);
    //TextureManager::GetInstance().LoadTextures("PlayGameBackgroundHover", "../images/game-states/start/PlayGameHover.png");
    //TextureManager::GetInstance().LoadTextures("SnakeTextStartScreen", "../images/game-states/start/SnakeTextStartScreen.png");
    //TextureManager::GetInstance().LoadTextures("SnakeBackgroundStart", "../images/game-states/start/SnakeStartBackground.png");

    snakeText->texture = TextureManager::GetInstance().GetTexture("SnakeTextStartScreen"); // SnakeBackgroundStart
    snakeBackground->texture = TextureManager::GetInstance().GetTexture("SnakeBackgroundStart");
    playGameText->texture = TextureManager::GetInstance().GetTexture("PlayGameTextBackground");

    /*snakeText->texture = TextureManager::GetInstance().allTextures.find("SnakeTextStartScreen")->second;
    snakeBackground->texture = TextureManager::GetInstance().allTextures.find("SnakeBackgroundStart")->second;
    playGameText->texture = TextureManager::GetInstance().allTextures.find("PlayGameBackground")->second;
*/
}

void StartState::Render() {
    snakeBackground->Render();
    snakeText->Render();
    playGameText->Render();



    FontManager::GetInstance().RenderFont("PLAY GAME  ", BLACK_COLOR, false,230, 500, 365, 70);
    //FontManager::GetInstance().RenderFont("PLAY GAME  ", BLACK_COLOR, false,312, 500, 350, 70);

}

void StartState::HandleInputs() {
    SDL_GetMouseState( &mouseXPos, &mouseYPos );
    if(mouseXPos > 208 && mouseXPos < 208+384 && mouseYPos > 500 && mouseYPos < 500+80){
        playGameText->texture = TextureManager::GetInstance().GetTexture("PlayGameTextBackgroundHover");
    } else{
        playGameText->texture = TextureManager::GetInstance().GetTexture("PlayGameTextBackground");
    }

    if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1))){
        if(mouseXPos > 208 && mouseXPos < 208+384 && mouseYPos > 500 && mouseYPos < 500+80){
            std::cout << "Mouse position x " << mouseXPos << ", y " << mouseYPos << std::endl;
            GameManager::GetInstance().SwitchToNextState();
        }
    }
}
