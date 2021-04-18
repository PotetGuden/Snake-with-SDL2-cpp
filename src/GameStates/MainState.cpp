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
    frameCounterSpeed(10),
    headerObject(std::make_unique<GameObject>(0,0,800,160)),
    score(0),
    timeLeft(50),
    lives(3),
    showNextLvlMessage(false),
    timerForNextLvLMessage(0)
    {
        Map::GetInstance().LoadNextLevel(currentLvl++);
        AddThreeDifferentFruits();
        ScoreManager::GetInstance().PrintScores();
        ScoreManager::GetInstance().SortScores();

        headerObject->texture = TextureManager::GetInstance().GetTexture("headerTexture");

        /*dummyVariable = std::async(std::launch::async, []() {
            while (GameManager::GetInstance().gameRunning)
                Snake::GetInstance().CheckForCollisions();
        });*/
}

void MainState::Render() {
    Map::GetInstance().RenderMap();
    Snake::GetInstance().Render();

    for(const auto &fruit : fruits){
        fruit->Render();
    }
    headerObject->Render();
    RenderHeaderText();
}

void MainState::RenderHeaderText() {
    SDL_Color textColor = { 255, 255, 255 ,255};
    FontManager::GetInstance().RenderFont("Score: " + std::to_string(score), BLACK_COLOR, false, 10, 10, 150, 60);
    FontManager::GetInstance().RenderFont("Time left: " + std::to_string(timeLeft), WHITE_COLOR, false, 570, 10, 150, 60);
    FontManager::GetInstance().RenderFont("Lives: " + std::to_string(lives), BLACK_COLOR, false,10, 90, 100, 60);
    FontManager::GetInstance().RenderFont("SNEEEK", GREEN_COLOR, false, 300, 5, 200, 100);
    FontManager::GetInstance().RenderFont("Highscore:  " + std::to_string(ScoreManager::GetInstance().GetHighScore()), BLACK_COLOR, false,312, 90, 175, 60);
    FontManager::GetInstance().RenderFont("Level: " + std::to_string(currentLvl), WHITE_COLOR, false, 570, 90, 150, 60);
    FontManager::GetInstance().RenderFont("Mute" , WHITE_COLOR, true, 175, 130, 75, 25);

    if(showNextLvlMessage) {
        enableMovement = false;
        bonusScoreText += (bonusScoreText < score) ? 1 : 0;
        FontManager::GetInstance().RenderFont(" Congratulations, you made it to ", WHITE_COLOR,true, 250, 380, 300, 45); // TODO
        FontManager::GetInstance().RenderFont(" level " + std::to_string(currentLvl) + ", your score is now " + std::to_string(bonusScoreText) + " ", WHITE_COLOR, true, 250, 425, 300, 45); // TODO


        if(bonusScoreText >= score){
            timerForNextLvLMessage++;
            if(timerForNextLvLMessage >= 100 ){
                showNextLvlMessage = false;
                enableMovement = true;
                timerForNextLvLMessage = 0;
            }
        }
    }
}

void MainState::Update() {

    InputManager::GetInstance().Update();
    HandleInputs();

    if((score >= 250 && score <= 270) || (score > 550 && score < 580)) GoToNextLvl();
    if( timeLeft == 50 ) frameCounterSpeed = 10;
    if( timeLeft == 40 ) frameCounterSpeed = 9;
    if( timeLeft == 30 ) frameCounterSpeed = 8;
    if( timeLeft == 15 ) frameCounterSpeed = 7;

    if(GameManager::GetInstance().frameCounter % frameCounterSpeed == 0) { // Speed at which snake moves.
        Snake::GetInstance().Update();
    }

    if(lives == 0 || timeLeft == 0){
       GameOver();
    } else{
        if((GameManager::GetInstance().frameCounter % 60) == 0){ // TODO Se nærmere på denne
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
        } else if(InputManager::GetInstance().KeyDown(SDL_SCANCODE_M)){
            AudioManager::GetInstance().MuteOrUnmuteSoundEffects();
        }

    } else if(!showNextLvlMessage){ // Sjekker først om det er en pause state som kjører
        if(im.KeyDown(SDL_SCANCODE_T)){  // Reset
            Snake::GetInstance().StartPosition();
            ScoreManager::GetInstance().AddScore("../scores/scores.txt", score);
            //ScoreManager::GetInstance().SortScores();
            lives = 20;
            timeLeft = 50;
            score = 0;
            enableMovement = true;
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
        bonusScoreText = score;  // use this to animate the bonus score you get
        score += timeLeft*5; // bonus points
        timeLeft = 50;
        lives = 3;
    } else{
        GameManager::GetInstance().SwitchToNextState();
    }
}

void MainState::AddThreeDifferentFruits() {
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::APPLE,BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE * 5,BLOCK_SIZE * 7 + 160));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::BANANA, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE * 10, BLOCK_SIZE * 7 + 160));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::WATERMELON, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE * 15, BLOCK_SIZE * 7 + 160));
}

void MainState::AddScore(const int number) {
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
}

void MainState::GameOver() const {
    AudioManager::GetInstance().PlaySound("gameOver");
    ScoreManager::GetInstance().AddScore("../scores/scores.txt", score);
    EndState::GetInstance().UpdateCurrentScore(score);
    Snake::GetInstance().StopSnake();
    GameManager::GetInstance().SwitchToNextState();
}




