//
// Created by Joste on 05.04.2021.
//

#include <iostream>
#include "../../include/GameStates/EndState.h"
#include "../../include/TextureManager.h"
#include "../../include/InputManager.h"
#include "../../include/GameManager.h"

constexpr SDL_Color BLACK_COLOR = {0, 0, 0, 0};
constexpr SDL_Color WHITE_COLOR = {255, 255, 255, 255};
constexpr SDL_Color GREEN_COLOR2 = {0, 255, 0, 255};

void EndState::Render() {
    endBackground->Render();
    FontManager::GetInstance().RenderFont("GAME OVER", WHITE_COLOR, false,320, 90, 150, 60);
    FontManager::GetInstance().RenderFont("YOUR SCORE WAS: 455", WHITE_COLOR, false,280, 250, 225, 60);
    FontManager::GetInstance().RenderFont("High Scores", WHITE_COLOR, true,300, 350, 200, 60);
    //FontManager::GetInstance().RenderFont("SNEEEK", GREEN_COLOR2, true, 300, 5, 200, 100);

    if(scores.size() < 5){
        for(int i = 0; i < scores.size(); i++){
            FontManager::GetInstance().RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ", SDL_Color{50,50,50,50}, true,300, 415+i*60, 200, 60);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            FontManager::GetInstance().RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ",SDL_Color{50, 50, 50, 50}, true, 300, 415 + i * 60, 200, 60);
        }
    }
}

EndState::EndState(){
    //FontManager::GetInstance().SetFont();
    endBackground = std::make_unique<GameObject>(0,0,800,800,TextureManager::GetInstance().LoadTexture("../images/EndScreen.png"));
    endBackground->texture = TextureManager::GetInstance().LoadTexture("../images/EndScreen.png");
    scoreManager = std::make_unique<ScoreManager>();
    scoreManager->GetScoresFromFile("../scores/scores.txt", scores);

    std::cout << "Score size = " << scores.size() << std::endl;
}

void EndState::HandleInputs() {
    if(InputManager::GetInstance().KeyDown(SDL_SCANCODE_Y)){
        GameManager::GetInstance().SwitchToNextState();
    }
}

