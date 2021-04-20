//
// Created by Joste on 10.03.2021.
//

#include <algorithm>
#include <future>
#include "../include/Snake.h"
#include "../include/GameManager.h"

Snake::Snake() :
        snakeSpeed(0),
        startPosition(true),
        isAbleToChangeDirection(true)
{
    // Push one part for body and one for tail
    snakeBodyVector.emplace_back(std::make_shared<SnakePart>());
    snakeBodyVector.emplace_back(std::make_shared<SnakePart>());

    StartPosition();

    dummyVariable = std::async(std::launch::async, [this]() {
        while (GameManager::GetInstance().gameRunning)
            CheckForCollisions();
    });
}

void Snake::MoveSnakeHead() {
    if(isNextTileWall.get() && snakeSpeed != 0){
        StopSnake();
        MainState::GetInstance().ReduceLives();
        AudioManager::GetInstance().PlaySound("crashSound");
    } else{
        if(snakeSpeed != 0 &&  !startPosition){
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
            }
            MoveBodyAndTail();
        }
    }
    isAbleToChangeDirection = true;
}

void Snake::MoveBodyAndTail() {
        SnakePart currPosition{};
        for(auto &snakePart : snakeBodyVector){
            currPosition.partDirection = snakePart->partDirection;
            currPosition.coords = snakePart->coords;

            snakePart->partDirection = prevPosition.partDirection;
            snakePart->coords = prevPosition.coords;

            prevPosition = currPosition;
        }

        // Jeg bruker snakeBodyVector.size()-2 fordi jeg vil ha nest siste element i vectoren, sånn at tail alltid følger den
        snakeBodyVector.back()->partDirection = snakeBodyVector[snakeBodyVector.size() - 2]->partDirection;
}

void Snake::Render() {
    snakeHead->Render();
    std::ranges::for_each(snakeBodyVector.begin(),snakeBodyVector.end(),[](auto &snakePart){
        snakePart->Render();
    });
}

void Snake::Grow(int xTimes) {
    SnakePart newPart{};

    for(int i = 0; i < xTimes; i++) {
        newPart = *snakeBodyVector.back();
        snakeBodyVector.emplace_back(std::make_shared<SnakePart>(newPart));
    }
}

void Snake::UpdateTexture() {
    // Head Texture
    switch(snakeHead->partDirection){
        case Direction::UP:
            snakeHead->angleTextureFlip = 270;
            snakeHead->renderFlip = SDL_FLIP_NONE;
            break;
        case Direction::DOWN:
            snakeHead->angleTextureFlip = 90;
            snakeHead->renderFlip = SDL_FLIP_NONE;
            break;
        case Direction::LEFT:
            snakeHead->angleTextureFlip = 180;
            snakeHead->renderFlip = SDL_FLIP_VERTICAL;
            break;
        case Direction::RIGHT:
            snakeHead->angleTextureFlip = 0;
            snakeHead->renderFlip = SDL_FLIP_NONE;
            break;
    }

    // Body Texture
    prevPosition = *snakeHead;
    for(int i = 0; i < snakeBodyVector.size() - 1; i++){
        if(SDL_HasIntersection(&snakeBodyVector[i]->coords, &snakeBodyVector.back()->coords)){ // When the snake grows, multiple bodyparts overlaps, this just ensures that it has a tail texture
            snakeBodyVector[i]->texture = snakeBodyVector.back()->texture;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::RIGHT ||
                  snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureRightDownUpLeft");
            snakeBodyVector[i]->angleTextureFlip = 270;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::LEFT ||
                  snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureRightDownUpLeft");
            snakeBodyVector[i]->angleTextureFlip = 0;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::RIGHT ||
                  snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::UP){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureRightDownUpLeft");
            snakeBodyVector[i]->angleTextureFlip = 180;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::LEFT ||
                  snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::UP){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureRightDownUpLeft");
            snakeBodyVector[i]->angleTextureFlip = 90;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::RIGHT && prevPosition.partDirection == Direction::RIGHT ||
                  snakeBodyVector[i]->partDirection == Direction::LEFT && prevPosition.partDirection == Direction::LEFT){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureUpDown");
            snakeBodyVector[i]->angleTextureFlip = 90;
            snakeBodyVector[i]->renderFlip = SDL_FLIP_NONE;
        } else if(snakeBodyVector[i]->partDirection == Direction::UP && prevPosition.partDirection == Direction::UP ||
                  snakeBodyVector[i]->partDirection == Direction::DOWN && prevPosition.partDirection == Direction::DOWN){
            snakeBodyVector[i]->texture = TextureManager::GetInstance().GetTexture("bodyTextureUpDown");
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

void Snake::UpdateHeadsNextMove() {
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
}

void Snake::ChangeDirection(Direction potentialDir, Direction oppositeDir) {
    if(snakeHead->partDirection != oppositeDir && isAbleToChangeDirection){
        snakeHead->partDirection = potentialDir;
        startPosition = false;
        isAbleToChangeDirection = false;
        snakeSpeed = 32;
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
    InitializeSnakePartsStartPosition();
}

void Snake::Update() {
    StartWallCollisionThread();
    MoveSnakeHead();
    UpdateTexture();
    prevPosition = *snakeHead;
}

void Snake::CheckForCollisions() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    // Snake Collision
    for (const auto &bodyPart: snakeBodyVector) {
        if (SDL_HasIntersection(&snakeHead->coords, &bodyPart->coords)) {
            AudioManager::GetInstance().PlaySound("snakeEatingSnake");
            MainState::GetInstance().ReduceLives();
            StartPosition();
        }
    }
    //Fruit Collision
    for (auto &fruit : MainState::GetInstance().GetFruitVector()) {
        if (SDL_HasIntersection(&fruit->coords, &snakeHead->coords)) {
            AudioManager::GetInstance().PlaySound("eatingFruit");
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
}

bool Snake::CheckNewFruitCollisionSnake(SDL_Rect& potentialPos) const {
    if(SDL_HasIntersection(&potentialPos, &snakeHead->coords))
        return true;

    return std::ranges::any_of(snakeBodyVector.begin(), snakeBodyVector.end(), [&potentialPos](auto &snakePart){
        return SDL_HasIntersection(&potentialPos, &snakePart->coords);
    });
}

void Snake::StartWallCollisionThread() {
    isNextTileWall = std::async(std::launch::async,[this](){
        UpdateHeadsNextMove();
        if(Map::GetInstance().CheckForWallCollision(headsNextMove)){
            snakeHead->partDirection = prevPosition.partDirection;
            return true;
        }
        return false;
    });
}

void Snake::InitializeSnakePartsStartPosition() {
    // Snake Head
    snakeHead->coords = { BLOCK_SIZE * 4, (BLOCK_SIZE * 5) + HEADER_TEXTURE_Y_OFFSET, BLOCK_SIZE, BLOCK_SIZE};
    snakeHead->angleTextureFlip = 0;
    snakeHead->texture = TextureManager::GetInstance().GetTexture("headTextureUp");
    snakeHead->partDirection = Direction::RIGHT;
    // Snake Middle Part
    snakeBodyVector[0]->coords = { BLOCK_SIZE * 3, (BLOCK_SIZE * 5) + HEADER_TEXTURE_Y_OFFSET, BLOCK_SIZE, BLOCK_SIZE};
    snakeBodyVector[0]->texture = TextureManager::GetInstance().GetTexture("bodyTextureUpDown");
    snakeBodyVector[0]->angleTextureFlip = 90.0;
    snakeBodyVector[0]->partDirection = Direction::RIGHT;
    // Snake Tail
    snakeBodyVector[1]->coords = { BLOCK_SIZE * 2, (BLOCK_SIZE * 5) + HEADER_TEXTURE_Y_OFFSET, BLOCK_SIZE, BLOCK_SIZE};
    snakeBodyVector[1]->texture = TextureManager::GetInstance().GetTexture("tailTextureRight");
    snakeBodyVector[1]->angleTextureFlip = 0;
    snakeBodyVector[1]->partDirection = Direction::RIGHT;

}


/*return std::ranges::any_of(Map::GetInstance().GetWallTiles().begin(), Map::GetInstance().GetWallTiles().end(), [this](auto &wallTile){
            if (SDL_HasIntersection(&headsNextMove, &wallTile.coords)) {
                snakeHead->partDirection = prevPosition.partDirection;
                return true;
            }
            return false;
        });*/