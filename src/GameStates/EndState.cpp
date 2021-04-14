//
// Created by Joste on 05.04.2021.
//

#include <iostream>
#include "../../include/GameStates/EndState.h"
#include "../../include/TextureManager.h"
#include "../../include/GameManager.h"

constexpr SDL_Color BLACK_COLOR = {0, 0, 0, 0};
constexpr SDL_Color WHITE_COLOR = {255, 255, 255, 255};
constexpr SDL_Color GREEN_COLOR = {0, 255, 0, 255};

// TODO gFont funker ikke her.. gjøre fontmanager til static?    -  det funker om man lager smart pointer i gamemanager av alle states.. funker ikke med GetInstance().Render()

void EndState::Render() {
    //endBackground->Render();
    std::cout << "End screen rendering start" << std::endl;
    //fontManager->RenderFont("GAME OVER", WHITE_COLOR, false,320, 90, 150, 60);
    //fontManager->RenderFont("High Scores", WHITE_COLOR, true,300, 170, 200, 60);
    fontManager->RenderFont("SNEEEK", GREEN_COLOR, false, 300, 5, 200, 100);

    /*if(scores.size() < 8){
        for(int i = 0; i < scores.size(); i++){
            fontManager->RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ", SDL_Color{50,50,50,50}, true,300, 235+i*60, 200, 60);
        }
    } else {
        for (int i = 0; i < 8; i++) {
            fontManager->RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ",SDL_Color{50, 50, 50, 50}, true, 300, 235 + i * 60, 200, 60);
        }
    }*/
    std::cout << "End screen rendering end" << std::endl;

}

EndState::EndState() :
    fontManager(std::make_shared<FontManager>())
    {
    endBackground = std::make_unique<GameObject>(0,0,800,800);
    //fontManager = std::make_shared<FontManager>();
    fontManager->SetFont();

    scoreManager = std::make_unique<ScoreManager>();
    scoreManager->GetScoresFromFile("../scores/scores.txt", scores);

    endBackground->texture = TextureManager::GetInstance().LoadTexture("../images/EndScreen.png");

    std::cout << "Score size = " << scores.size() << std::endl;
}
