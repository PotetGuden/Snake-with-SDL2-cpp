//
// Created by Joste on 05.04.2021.
//

#include <iostream>
#include <future>
#include "../../include/GameStates/MainState.h"
#include "../../include/GameManager.h"


constexpr SDL_Color BLACK_COLOR = {0, 0, 0, 0};
constexpr SDL_Color WHITE_COLOR = {255, 255, 255, 255};
constexpr SDL_Color GREEN_COLOR = {0, 255, 0, 255};

// TODO lage en Player class som inneholde score/liv/timeleft osv

MainState::MainState() :
    currentLvl(0),
    fontManager(std::make_unique<FontManager>()),
    scoreManager(std::make_unique<ScoreManager>()),
    enableMovement(true),
    frameCounterSpeed(10),
    headerObject(std::make_unique<GameObject>(0,0,800,160)),
    score(0),
    timeLeft(50),
    lives(20),
    showNextLvlMessage(false),
    timer(0)
    {
        Map::GetInstance().LoadNextLevel(currentLvl++);

        AddThreeDifferentApples();

        scoreManager->PrintScores();
        scoreManager->SortScores();

        TTF_Init();
        fontManager->SetFont();

        headerObject->texture = TextureManager::GetInstance().LoadTexture("../images/header.png");

        dummyVariable = std::async(std::launch::async, []() {
            while (GameManager::GetInstance().gameRunning)
                Snake::GetInstance().CheckForCollisions();
        });
}

void MainState::Render() {
    Map::GetInstance().DrawMap();
    Snake::GetInstance().Render();

    for(const auto &fruit : fruits){
        fruit->Render();
    }
    headerObject->Render();
    RenderHeaderText();
}

void MainState::RenderHeaderText() {
    SDL_Color textColor = { 255, 255, 255 ,255};
    fontManager->RenderFont("Score: " + std::to_string(score), BLACK_COLOR, false, 10, 10, 150, 60);
    fontManager->RenderFont("Time left: " + std::to_string(timeLeft), WHITE_COLOR, false, 570, 10, 150, 60);
    fontManager->RenderFont("Lives: " + std::to_string(lives), BLACK_COLOR, false,10, 90, 100, 60);
    fontManager->RenderFont("SNEEEK", GREEN_COLOR, false, 300, 5, 200, 100);
    fontManager->RenderFont("Highscore:  " + std::to_string(scoreManager->GetHighScore()), BLACK_COLOR, false,312, 90, 175, 60);
    fontManager->RenderFont("Level: " + std::to_string(currentLvl), WHITE_COLOR, false, 570, 90, 150, 60);

    if(showNextLvlMessage) {
        enableMovement = false;
        bonusScoreText += (bonusScoreText < score) ? 1 : 0;
        fontManager->RenderFont(" Congratulations, you made it to ", BLACK_COLOR,true, 250, 380, 300, 45); // TODO
        fontManager->RenderFont(" level " + std::to_string(currentLvl) + " and you score is now " + std::to_string(bonusScoreText) + " ", BLACK_COLOR, true, 250, 425, 300, 45); // TODO

        if(bonusScoreText >= score){
            timer++;
            if(timer >= 100 && InputManager::GetInstance().KeyStillDown(SDL_SCANCODE_N)){
                showNextLvlMessage = false;
                timer = 0;
                enableMovement = true;
                std::cout << "Trykket på N" << std::endl;
            }
        }
    }
}

void MainState::Update() {

    InputManager::GetInstance().Update();
    HandleInputs();

    if( score == 10000 ) {
        GoToNextLvl();
    }

    /*
     * [&ptr](){
        return ptr->foo();
     * */




    /*for(auto &fruit : fruits) {
        if (FruitEaten(fruit)) {
            if(fruit->type == Fruit::TYPE::APPLE){
                Snake::GetInstance().Grow(1);
                score += 10;
            } else if(fruit->type == Fruit::TYPE::BANANA){
                score += 20;
                Snake::GetInstance().Grow(2);
            } else if(fruit->type == Fruit::TYPE::WATERMELON){
                score += 30;
                Snake::GetInstance().Grow(3);
            }
            fruit->SetNewPosition();
            std::cout << "Fruit eaten" << std::endl;
        }
    }*/

    //if(timeLeft == 45) frameCounterSpeed = 4;
    //if(timeLeft == 40) frameCounterSpeed = 3;
    //if(timeLeft == 35) frameCounterSpeed = 2;
    //if(timeLeft == 30) frameCounterSpeed = 1;

    if(score > 100 && score < 200)
        frameCounterSpeed = 8;
    if(score >= 200 )
        frameCounterSpeed = 5;

    if(GameManager::GetInstance().frameCounter % frameCounterSpeed == 0) { // finne ny metode?
        Snake::GetInstance().StartWallCollisionThread();
        Snake::GetInstance().MoveSnakeHead();
        //Snake::GetInstance().MoveBodyAndTail();
        Snake::GetInstance().UpdateTexture();
        Snake::GetInstance().Update();
        //boool  = true;
    }

    if(lives != 0 && timeLeft > 0){
        if((GameManager::GetInstance().frameCounter % 60) == 0){ // TODO Se nærmere på denne
            timeLeft--;
        }
    } else{
        Snake::GetInstance().StopSnake();
        enableMovement = false;
    }
}

void MainState::HandleInputs() {
    InputManager &im = InputManager::GetInstance();

    if(im.KeyDown(SDL_SCANCODE_ESCAPE) || SDL_HasEvent(SDL_QUIT)){
        GameManager::GetInstance().gameRunning = false;
    }
    // Keyboard testing - Trenger en thread for at man ikke kan trykke 2 knapper samtidig ish
    if(enableMovement){
        if(im.KeyDown(SDL_SCANCODE_W)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::UP, Snake::Direction::DOWN);
        } else if(im.KeyDown(SDL_SCANCODE_S)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::DOWN, Snake::Direction::UP);
        } else if(im.KeyDown(SDL_SCANCODE_A)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::LEFT, Snake::Direction::RIGHT);
        } else if(im.KeyDown(SDL_SCANCODE_D)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::RIGHT, Snake::Direction::LEFT);
        } else if(im.KeyDown(SDL_SCANCODE_R)){
            Snake::GetInstance().ChangeDirection(Snake::Direction::NONE, Snake::Direction::NONE);
            Map::GetInstance().MapTest();
        }
    } else if(!showNextLvlMessage){ // Sjekker først om det er en pause state som kjører
        if(im.KeyDown(SDL_SCANCODE_T)){  // Reset
            Snake::GetInstance().StartPosition();
            scoreManager->AddScore("../scores/scores.txt", score);
            scoreManager->SortScores();
            lives = 20;
            timeLeft = 50;
            score = 0;
            enableMovement = true;
            frameCounterSpeed = 8;
        }
    }
}

void MainState::GoToNextLvl() {
    showNextLvlMessage = true;
    GameManager::GetInstance().gameRunning = Map::GetInstance().LoadNextLevel(currentLvl++);
    Snake::GetInstance().StartPosition();
    bonusScoreText = score;  // use this to animate the bonus score you get
    score += timeLeft*5; // bonus points
    timeLeft = 50;
    lives = 20;
}


void MainState::AddThreeDifferentApples() {
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::APPLE,BLOCK_SIZE,BLOCK_SIZE,128,256));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::BANANA, BLOCK_SIZE, BLOCK_SIZE, 224, 448));
    fruits.emplace_back(std::make_shared<Fruit>(Fruit::TYPE::WATERMELON, BLOCK_SIZE, BLOCK_SIZE, 384, 480));
}

void MainState::AddScore(const int number) {
    score += number;
}

void MainState::ReduceLives() {
    lives--;
}

std::vector<std::shared_ptr<Fruit>> &MainState::GetFruitVector() {
    return fruits;
}




