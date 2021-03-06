//
// Created by Joste on 05.04.2021.
//

#include <memory>

#include "../../include/GameStates/StartState.h"
#include "../../include/GameManager.h"

StartState::StartState() :
    snakeText(std::make_unique<GameObject>(208,304,384,192,TextureManager::GetInstance().GetTexture("SnakeTextStartScreen"))),
    snakeBackground(std::make_unique<GameObject>(0,0,800,800, TextureManager::GetInstance().GetTexture("SnakeBackgroundStart"))),
    playGameText(std::make_unique<GameObject>(208,500,384,80, TextureManager::GetInstance().GetTexture("PlayGameTextBackground"))),
    showRules(false)
{
}

void StartState::Render() {
    snakeBackground->Render();
    snakeText->Render();
    playGameText->Render();

    FontManager::GetInstance().RenderFont("PLAY GAME  ", BLACK_COLOR, false,230, 500, 365, 70);
    FontManager::GetInstance().RenderFont(" RULES ", ruleTextColor, true ,325, 700, 150, 40);

    if(showRules){
        FontManager::GetInstance().RenderFont("           RULES           ", WHITE_COLOR, true, 200, 200,390,60);
        FontManager::GetInstance().RenderFont( " Eat fruit to gain points each fruit ", RED_COLOR, true, 200, 260,390,60);
        FontManager::GetInstance().RenderFont( "   give different points and size   ", RED_COLOR, true, 200, 320,390,60);
        FontManager::GetInstance().RenderFont( " If you eat snake or hit the wall  ", GREEN_COLOR, true, 200, 380,390,60);
        FontManager::GetInstance().RenderFont( "         You will lose 1 life           ", GREEN_COLOR, true, 200, 440,390,60);
        FontManager::GetInstance().RenderFont( " Achieve a certain score to reach the ", RED_COLOR, true, 200, 500,390,60);
        FontManager::GetInstance().RenderFont( "               Next level               ", RED_COLOR, true, 200, 560,390,60);
        FontManager::GetInstance().RenderFont( " Press M to mute or unmute sound effects ", GREEN_COLOR, true, 200, 620,390,60);
    }
}

void StartState::HandleInputs() {
    SDL_GetMouseState( &mouseXPos, &mouseYPos );

    // Play Game button
    if(mouseXPos > 208 && mouseXPos < 592 && mouseYPos > 500 && mouseYPos < 580){
        playGameText->texture = TextureManager::GetInstance().GetTexture("PlayGameTextBackgroundHover");
        if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1)))
            GameManager::GetInstance().SwitchToNextState();
    } else{
        playGameText->texture = TextureManager::GetInstance().GetTexture("PlayGameTextBackground");
    }

    // Rules button
    if(mouseXPos > 325 && mouseXPos < 475 && mouseYPos > 700 && mouseYPos < 740){
        ruleTextColor = GREEN_COLOR;
        if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1)))
            showRules = !showRules;
    } else{
        ruleTextColor = WHITE_COLOR;
    }


}
