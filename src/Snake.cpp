//
// Created by Joste on 10.03.2021.
//

#include <iostream>
#include <algorithm>
#include <future>
#include <fstream>
#include "../include/Snake.h"
#include "../include/GameManager.h"

// Todo fikse at snake texture ikke bugger seg når direction er none
// TODO kanskje bytte at når snake stopper så blir dir = none til snakespeed = 0

void Snake::MoveBodyAndTail() {
    //if(snakeHead->partDirection != Direction::NONE) {
    if(snakeSpeed != 0 && snakeHead->partDirection != Direction::NONE) {
        for(auto &snakePart : snakeBodyVector){
                /*SnakePart currPosition = *snakePart;
                *snakePart = prevPosition;
                prevPosition = currPosition;*/
                SnakePart currPosition{};
                currPosition.partDirection = snakePart->partDirection;
                currPosition.coords = snakePart->coords;

                snakePart->partDirection = prevPosition.partDirection;
                snakePart->coords = prevPosition.coords;

                prevPosition = currPosition;
        }

        // Jeg bruker snakeBodyVector.size()-2 fordi jeg vil ha nest siste element i vectoren, sånn at tail alltid følger den
        if(snakeBodyVector[snakeBodyVector.size() - 2]->partDirection != Direction::NONE) {
            snakeBodyVector.back()->partDirection = snakeBodyVector[snakeBodyVector.size() - 2]->partDirection;
        }

        //UpdateTexture();
    }
}

void Snake::Render() {
    //for(auto &snakePart : snakeBodyVector){
    //    SDL_RenderCopy(GameManager::renderer,snakePart.texture, nullptr, &snakePart.coords);
    //}
    //SDL_RenderCopy(GameManager::renderer,snakeHead->texture, nullptr, &snakeHead->coords);
    snakeHead->Render();
    std::for_each(snakeBodyVector.begin(),snakeBodyVector.end(),[](std::shared_ptr<SnakePart> &snakePart){
        //SDL_RenderCopy(GameManager::renderer,snakePart->texture, nullptr, &snakePart->coords);
        snakePart->Render();
    });

    //SDL_RenderCopyEx(GameManager::renderer,TextureManager::GetInstance().allTextures.find("headTextureUp")->second, nullptr, &headsNextMove, 0, nullptr, SDL_FLIP_NONE);
}

Snake::~Snake() {
    std::cout << "SNake is KILl" << std::endl;
}


Snake::Snake() {
    TextureManager::GetInstance().LoadTextures("headTextureUp", "../images/SnakeHeadUp.png",0);
    TextureManager::GetInstance().LoadTextures("bodyTextureUpDown", "../images/SnakeBodyUpDown.png",0);
    TextureManager::GetInstance().LoadTextures("bodyTextureRightDownUpLeft", "../images/SnakeBodyRightDownUpLeft.png",0);
    TextureManager::GetInstance().LoadTextures("tailTextureRight", "../images/SnakeTailRight.png",270);

    // Start position Head
    snakeHeadStart.coords = SetSnakePartCoords(BLOCK_SIZE * 5, BLOCK_SIZE * 4 + 160); // 160 offset
    snakeHeadStart.texture = TextureManager::GetInstance().allTextures.find("headTextureUp")->second;
    snakeHeadStart.partDirection = Direction::RIGHT;
    snakeHeadStart.angleTextureFlip = 90;
    *snakeHead = snakeHeadStart;
    // Start Position Body
    snakeBodyStart.coords = SetSnakePartCoords(BLOCK_SIZE * 4, BLOCK_SIZE * 4 + 160);
    snakeBodyStart.texture = TextureManager::GetInstance().allTextures.find("bodyTextureUpDown")->second;
    snakeBodyStart.angleTextureFlip = 90;
    snakeBodyStart.partDirection = Direction::RIGHT;
    // Start Position Tail
    snakeTailStart.coords = SetSnakePartCoords(BLOCK_SIZE * 3, BLOCK_SIZE * 4 + 160);
    snakeTailStart.texture = TextureManager::GetInstance().allTextures.find("tailTextureRight")->second;
    snakeTailStart.partDirection = snakeBodyStart.partDirection;
    snakeHeadStart.angleTextureFlip = 0;

    snakeBodyVector.emplace_back(std::make_shared<SnakePart>(snakeBodyStart));
    snakeBodyVector.emplace_back(std::make_shared<SnakePart>(snakeTailStart));

    snakeSpeed = 0;
    startPosition = true;
}

void Snake::Grow(int xTimes) { // bare copy hele newPart -> .back()
    SnakePart newPart{};

    for(int i = 0; i < xTimes; i++) {
        newPart = *snakeBodyVector.back();
        snakeBodyVector.emplace_back(std::make_shared<SnakePart>(newPart));
    }
}

SDL_Rect Snake::SetSnakePartCoords(int x, int y) { // kanskje legg inn SDL_Rect tmpCoords her
    SDL_Rect tmpCoords;
    tmpCoords.x = x;
    tmpCoords.y = y;
    tmpCoords.w = BLOCK_SIZE;
    tmpCoords.h = BLOCK_SIZE;
    return tmpCoords;
}

void Snake::UpdateTexture() {
    auto lol = TextureManager::GetInstance().allTextures.find("headTextureUp");

    // Head Texture
    switch(snakeHead->partDirection){
        case Direction::UP:
            snakeHead->angleTextureFlip = 0;
            snakeHead->renderFlip = SDL_FLIP_HORIZONTAL;
            break;
        case Direction::DOWN:
            snakeHead->angleTextureFlip = 180;
            snakeHead->renderFlip = SDL_FLIP_NONE;
            break;
        case Direction::LEFT:
            snakeHead->angleTextureFlip = 270;
            snakeHead->renderFlip = SDL_FLIP_HORIZONTAL;
            break;
        case Direction::RIGHT:
            snakeHead->angleTextureFlip = 90;
            snakeHead->renderFlip = SDL_FLIP_NONE;
            break;
        case Direction::NONE:
            break;
    }

    // Body Texture
    prevPosition = *snakeHead;
    for(int i = 0; i < snakeBodyVector.size() - 1; i++){ // dropper tail
        if(SDL_HasIntersection(&snakeBodyVector[i]->coords, &snakeBodyVector.back()->coords)){ // When the snake grows, multiple bodyparts overlaps, this just ensures that it then has a tail texture
            snakeBodyVector[i]->texture = snakeBodyVector.back()->texture;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::RIGHT ||
           snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureRightDownUpLeft")->second;
            snakeBodyVector[i]->angleTextureFlip = 270;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::LEFT ||
                  snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureRightDownUpLeft")->second;
            snakeBodyVector[i]->angleTextureFlip = 0;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::RIGHT ||
                  snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::UP){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureRightDownUpLeft")->second;
            snakeBodyVector[i]->angleTextureFlip = 180;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::LEFT ||
                  snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::UP){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureRightDownUpLeft")->second;
            snakeBodyVector[i]->angleTextureFlip = 90;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::RIGHT ||
                  snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::LEFT){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureUpDown")->second;
            snakeBodyVector[i]->angleTextureFlip = 90;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::UP ||
                  snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().allTextures.find("bodyTextureUpDown")->second;
            snakeBodyVector[i]->angleTextureFlip = 0;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        }
        prevPosition = *snakeBodyVector[i];
    }
    // Tail Texture
    if(snakeBodyVector.back()->partDirection == Direction::UP){
        snakeBodyVector.back()->angleTextureFlip = 270;
        snakeBodyVector.back()->renderFlip = SDL_FLIP_VERTICAL;
    } else if(snakeBodyVector.back()->partDirection == Direction::DOWN){
        snakeBodyVector.back()->angleTextureFlip = 90;
        snakeBodyVector.back()->renderFlip = SDL_FLIP_NONE;
    } else if(snakeBodyVector.back()->partDirection == Direction::LEFT){
        snakeBodyVector.back()->angleTextureFlip = 180;
        snakeBodyVector.back()->renderFlip = SDL_FLIP_VERTICAL;
    } else if(snakeBodyVector.back()->partDirection == Direction::RIGHT){
        snakeBodyVector.back()->angleTextureFlip = 0;
        snakeBodyVector.back()->renderFlip = SDL_FLIP_NONE;
    }
}

SDL_Rect Snake::HeadsNextMove() {
    headsNextMove.w = BLOCK_SIZE;
    headsNextMove.h = BLOCK_SIZE;
    if (snakeHead->partDirection == Direction::UP) {
        headsNextMove.x = snakeHead->coords.x;
        headsNextMove.y = snakeHead->coords.y - BLOCK_SIZE;
    } else if (snakeHead->partDirection == Direction::DOWN) {
        headsNextMove.x = snakeHead->coords.x;
        headsNextMove.y = snakeHead->coords.y + BLOCK_SIZE;
    } else if (snakeHead->partDirection == Direction::LEFT) {
        headsNextMove.x = snakeHead->coords.x - BLOCK_SIZE;
        headsNextMove.y = snakeHead->coords.y;
    } else if (snakeHead->partDirection == Direction::RIGHT) {
        headsNextMove.x = snakeHead->coords.x + BLOCK_SIZE;
        headsNextMove.y = snakeHead->coords.y;
    }
    return headsNextMove;
}

void Snake::ChangeDirection(const Direction potentialDir, const Direction oppositeDir) {
    if(snakeHead->partDirection != oppositeDir && isAbleToChangeDirection){
        snakeHead->partDirection = potentialDir;
        startPosition = false;
        snakeSpeed = 32;
        isAbleToChangeDirection = false;
    }
}

void Snake::MoveSnakeHead() {
    if(isNextTileWall.get() && snakeSpeed != 0){
        StopSnake();
        MainState::GetInstance().ReduceLives();
    } else{
        if(snakeSpeed != 0 && !startPosition){
            switch (snakeHead->partDirection) {
                case Direction::UP:
                    snakeHead->coords.y -= snakeSpeed;
                    break;
                case Direction::DOWN:
                    snakeHead->coords.y += snakeSpeed;
                    break;
                case Direction::LEFT:
                    snakeHead->coords.x -= snakeSpeed;
                    break;
                case Direction::RIGHT:
                    snakeHead->coords.x += snakeSpeed;
                    break;
                case Direction::NONE:
                    break;
            }
            MoveBodyAndTail();
        }
    }
}

void Snake::StopSnake() {
    snakeSpeed = 0;
}

void Snake::StartPosition() {
    startPosition = true;
    if(snakeBodyVector.size() > 2){
        snakeBodyVector.erase(snakeBodyVector.begin() + 2, snakeBodyVector.end());
    }

    *snakeHead = snakeHeadStart;
    *snakeBodyVector[0] = snakeBodyStart;
    *snakeBodyVector[1] = snakeTailStart;
}

void Snake::Update() {
    //if(snakeHead->partDirection != Direction::NONE)
    prevPosition = *snakeHead;
    isAbleToChangeDirection = true;
}

std::mutex collisionMutex;
void Snake::CheckForCollisions() { // TODO DEL OPP
    std::this_thread::sleep_for(std::chrono::milliseconds(5) );
    //while (GameManager::GetInstance().gameRunning) {
    //std::lock_guard<std::mutex> lock(collisionMutex); //lock_guard unlocker mutex i sin destructor, dvs hver gang denne funksjonen er ferdig
    for (const auto &bodyPart: snakeBodyVector) {
        if (SDL_HasIntersection(&snakeHead->coords, &bodyPart->coords)) {
            MainState::GetInstance().ReduceLives();

            StartPosition();
            //SDL_Delay(1000); // funker ikke med multithread
            std::cout << "SNAKE HIT" << std::endl;
        }
    }
    for (auto &fruit : MainState::GetInstance().GetFruitVector()) {
        if (SDL_HasIntersection(&fruit->coords, &snakeHead->coords)) {
            std::cout << "FRUIT EATEN" << std::endl;
            switch (fruit->type) {
                case Fruit::TYPE::APPLE:
                    Grow(1);
                    MainState::GetInstance().AddScore(10);
                    break;
                case Fruit::TYPE::BANANA:
                    Grow(2);
                    MainState::GetInstance().AddScore(20);
                    break;
                case Fruit::TYPE::WATERMELON:
                    Grow(3);
                    MainState::GetInstance().AddScore(30);
                    break;
            }
            fruit->SetNewPosition();
        }
    }
    //SDL_Rect tmp = HeadsNextMove();
    //for (auto &wallTile : Map::GetInstance().GetWallTiles()) {
        //if (SDL_HasIntersection(&wallTile.coords, &tmp) && snakeHead->partDirection != Direction::NONE) {
            //std::cout << "Collided with wall!!" << std::endl;
            //StopSnake();
            //isColliding = true;
            //StartPosition();
            //MainState::GetInstance().ReduceLives();
       // }
    //}
    //if(snakeSpeed != 0){
       /* headsNextMove = HeadsNextMove();
        for (auto &wall : Map::GetInstance().GetWallTiles()) {
            if (SDL_HasIntersection(&headsNextMove, &wall.coords) && snakeHead->partDirection != Direction::NONE) {
                //MainState::GetInstance().ReduceLives();
                StopSnake();
                isColliding = true;
                snakeHead->texture = prevPosition.texture;
                snakeHead->partDirection = prevPosition.partDirection;
            }
        }*/
    //}
}

bool Snake::CheckNewFruitCollisionSnake(SDL_Rect potentialPos) {
    std::cout << "CheckNewFruitCollisionSnake has been run" << std::endl;
    if(SDL_HasIntersection(&potentialPos, &Snake::GetInstance().snakeHead->coords)){
        return true;
    }
    for(auto &snakePart : Snake::GetInstance().snakeBodyVector){
        if(SDL_HasIntersection(&potentialPos, &snakePart->coords)){
            return true;
        }
    }
    return false;
}

void Snake::StartWallCollisionThread() {
    isNextTileWall = std::async(std::launch::async,[this](){
        headsNextMove = HeadsNextMove();
        for (auto &wall : Map::GetInstance().GetWallTiles()) {
            if (SDL_HasIntersection(&headsNextMove, &wall.coords) && snakeHead->partDirection != Direction::NONE) {
                snakeHead->partDirection = prevPosition.partDirection;
                return true;
            }
        }
        return false;
    });
}
