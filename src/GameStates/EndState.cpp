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
constexpr SDL_Color RED_COLOR = {255, 0, 0};

void EndState::Render() {
    endBackground->Render();
    FontManager::GetInstance().RenderFont("GAME OVER", RED_COLOR, false,320, 90, 150, 60);
    FontManager::GetInstance().RenderFont("YOUR SCORE IS: " + std::to_string(currentScore), WHITE_COLOR, false,280, 220, 240, 60);
    FontManager::GetInstance().RenderFont(" High Scores ", WHITE_COLOR, true,300, 300, 200, 60);
    //FontManager::GetInstance().RenderFont("SNEEEK", GREEN_COLOR2, true, 300, 5, 200, 100);

    if(scores.size() < 5){
        for(int i = 0; i < scores.size(); i++){
            FontManager::GetInstance().RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ", BLACK_COLOR, true,300, 365+i*60, 200, 60);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            FontManager::GetInstance().RenderFont("  " + std::to_string(i+1) + ":    " + std::to_string(scores[i]) + "      ", BLACK_COLOR, true, 300, 365 + i * 60, 200, 60);
        }
    }

    FontManager::GetInstance().RenderFont(" PLAY AGAIN ", WHITE_COLOR, true,195, 700, 200, 60);
    FontManager::GetInstance().RenderFont(" EXIT GAME ", WHITE_COLOR, true,405, 700, 200, 60);
}

EndState::EndState(){
    //FontManager::GetInstance().SetFont();
    endBackground = std::make_unique<GameObject>(0,0,800,800,TextureManager::GetInstance().GetTexture("endScreenTexture"));
    //endBackground->texture = TextureManager::GetInstance().LoadTexture("../images/game-states/end/EndScreen.png");
    //scoreManager = std::make_unique<ScoreManager>();
    ScoreManager::GetInstance().GetScoresFromFile("../scores/scores.txt", scores);

    std::cout << "Score size = " << scores.size() << std::endl;
}

void EndState::HandleInputs() {
    SDL_GetMouseState( &mouseXPos, &mouseYPos );
    if(InputManager::GetInstance().MouseDown(SDL_BUTTON(1))){
        if(mouseXPos > 195 && mouseXPos < 195+200 && mouseYPos > 700 && mouseYPos < 700+60){
            MainState::GetInstance().RestartGame();
        }
        if(mouseXPos > 405 && mouseXPos < 405+200 && mouseYPos > 700 && mouseYPos < 700+60){
            GameManager::GetInstance().gameRunning = false;
        }
    }
}

void EndState::UpdateCurrentScore(int score) {
    currentScore = score;
    //ScoreManager::GetInstance().SortScores();
    ScoreManager::GetInstance().GetScoresFromFile("../scores/scores.txt", scores);
}


