//
// Created by Joste on 05.04.2021.
//

#include <iostream>
#include <future>
#include "../../include/GameStates/MainState.h"
#include "../../include/GameManager.h"


MainState::MainState() :
        currentLvl(0),
        enableMovement(true),
        xTimesSlowerThenFPS(13),
        headerObject(std::make_unique<GameObject>(0,0,800,160,TextureManager::GetInstance().GetTexture("headerTexture"))),
        score(0),
        timeLeft(50),
        lives(3),
        showNextLvlMessage(false),
        timerForNextLvLMessage(0),
        animateBonusScoreText(0)
    {
        Map::GetInstance().LoadNextLevel(currentLvl++);
        AddThreeDifferentFruits();
        ScoreManager::GetInstance().LoadScores();
        ScoreManager::GetInstance().SortScores();
}

void MainState::Render() {
    Map::GetInstance().RenderMap();
    Snake::GetInstance().Render();

    for(const auto &fruit : fruits){
        fruit->Render();
    }
    headerObject->Render();
    RenderHeaderText();

    if(showNextLvlMessage)
        RenderNextLvlMessage();
}

void MainState::RenderHeaderText() const {
    FontManager::GetInstance().RenderFont("Score: " + std::to_string(score), BLACK_COLOR, false, 10, 10, 150, 60);
    FontManager::GetInstance().RenderFont("Time left: " + std::to_string(timeLeft), WHITE_COLOR, false, 570, 10, 150, 60);
    FontManager::GetInstance().RenderFont("Lives: " + std::to_string(lives), BLACK_COLOR, false,10, 90, 100, 60);
    FontManager::GetInstance().RenderFont("SNEEEK", GREEN_COLOR, false, 300, 5, 200, 100);
    FontManager::GetInstance().RenderFont("Highscore:  " + std::to_string(ScoreManager::GetInstance().GetHighScore()), BLACK_COLOR, false,312, 90, 175, 60);
    FontManager::GetInstance().RenderFont("Level: " + std::to_string(currentLvl), WHITE_COLOR, false, 570, 90, 150, 60);
    FontManager::GetInstance().RenderFont("Mute" , WHITE_COLOR, true, 175, 130, 75, 25);

}

void MainState::RenderNextLvlMessage() {
    enableMovement = false;
    animateBonusScoreText += (animateBonusScoreText < score) ? 1 : 0;
    FontManager::GetInstance().RenderFont(" Congratulations, you made it to ", WHITE_COLOR,true, 250, 380, 300, 45);
    FontManager::GetInstance().RenderFont(" level " + std::to_string(currentLvl) + ", your score is now " + std::to_string(animateBonusScoreText) + " ", WHITE_COLOR, true, 250, 425, 300, 45);

    if(animateBonusScoreText >= score){ // Making a short delay after bonus score animation is done
        timerForNextLvLMessage++;
        if(timerForNextLvLMessage >= 100 ){
            showNextLvlMessage = false;
            enableMovement = true;
            timerForNextLvLMessage = 0;
        }
    }
}


void MainState::Update() {

    InputManager::GetInstance().Update();
    HandleInputs();

    if((score >= 250 && score <= 270) || (score > 550 && score < 580))
        GoToNextLvl();

    DecreaseSpeedOverTime();

    if(GameManager::GetInstance().frameCounter % xTimesSlowerThenFPS == 0) // Speed at which snake moves.
        Snake::GetInstance().Update();


    if(lives == 0 || timeLeft == 0){
       GameOver();
    } else{
        if((GameManager::GetInstance().frameCounter % 60) == 0){
            timeLeft--;
        }
    }
}

void MainState::HandleInputs() {
    InputManager &im = InputManager::GetInstance();

    if(enableMovement){
        if(im.KeyDown(SDL_SCANCODE_W)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::UP, Snake::Direction::DOWN);
        } else if(im.KeyDown(SDL_SCANCODE_S)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::DOWN, Snake::Direction::UP);
        } else if(im.KeyDown(SDL_SCANCODE_A)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::LEFT, Snake::Direction::RIGHT);
        } else if(im.KeyDown(SDL_SCANCODE_D)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::RIGHT, Snake::Direction::LEFT);
        } else if(im.KeyDown(SDL_SCANCODE_P)){
            GameManager::GetInstance().SwitchToNextState();
        } else if(im.KeyDown(SDL_SCANCODE_M)){
            AudioManager::GetInstance().MuteOrUnmuteSoundEffects();
        }
    }
}

void MainState::GoToNextLvl() {
    if(Map::GetInstance().LoadNextLevel(currentLvl++)){
        for(auto& fruit : fruits){
            fruit->SetNewPosition();
        }
        showNextLvlMessage = true;
        Snake::GetInstance().StartPosition();
        animateBonusScoreText = score;  // use this to animate the bonus score you get
        score += timeLeft*5;
        timeLeft = 50;
        lives = 3;
    } else{
        GameManager::GetInstance().SwitchToNextState();
    }
}

void MainState::AddThreeDifferentFruits() {
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::APPLE,BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE * 6,BLOCK_SIZE * 9 + 160));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::BANANA, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE * 11, BLOCK_SIZE * 9 + 160));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::WATERMELON, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE * 16, BLOCK_SIZE * 9 + 160));
}

void MainState::AddScore(const int& number) {
    score += number;
}

void MainState::ReduceLives() {
    lives--;
}

std::vector<std::shared_ptr<Fruit>>& MainState::GetFruitVector(){
    return fruits;
}

void MainState::RestartGame() {
    GameManager::GetInstance().SwitchToNextState();
    Snake::GetInstance().StartPosition();
    lives = 3;
    timeLeft = 50;
    score = 0;
    currentLvl = 0;
    Map::GetInstance().LoadNextLevel(currentLvl++);
    for(auto& fruit : fruits){
        fruit->SetNewPosition();
    }
}

void MainState::GameOver() const {
    AudioManager::GetInstance().PlaySound("gameOver");
    ScoreManager::GetInstance().AddScore("../res/scores/scores.txt", score);
    EndState::GetInstance().UpdateCurrentScore(score);
    Snake::GetInstance().StopSnake();
    GameManager::GetInstance().SwitchToNextState();
}

void MainState::DecreaseSpeedOverTime() {
    if( timeLeft == 50 ) xTimesSlowerThenFPS = 11;
    if( timeLeft == 40 ) xTimesSlowerThenFPS = 9;
    if( timeLeft == 30 ) xTimesSlowerThenFPS = 8;
    if( timeLeft == 15 ) xTimesSlowerThenFPS = 7;
}





