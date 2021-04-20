//
// Created by Joste on 26.03.2021.
//

#include "../include/Fruit.h"
#include "../include/GameManager.h"
#include <random>
#include <algorithm>


void Fruit::SetNewPosition() {
    SetNewRandomTexture();

    SDL_Rect potentialFruitPos;
    potentialFruitPos.w = BLOCK_SIZE;
    potentialFruitPos.h = BLOCK_SIZE;

    do {
        int x = GetRandomNumber(23) * BLOCK_SIZE; // x = 23, y = 18 because map size is [25][20] and we take -1 for each side (top/bottom) (left/right)
        int y = GetRandomNumber(18) * BLOCK_SIZE + HEADER_TEXTURE_Y_OFFSET;
        potentialFruitPos.x = x;
        potentialFruitPos.y = y;
    }
    while(Map::GetInstance().CheckForWallCollision(potentialFruitPos) ||
          Snake::GetInstance().CheckNewFruitCollisionSnake(potentialFruitPos) ||
          CheckFruitOnFruitCollision(potentialFruitPos));

    coords.x = potentialFruitPos.x;
    coords.y = potentialFruitPos.y;
    coords.w = BLOCK_SIZE;
    coords.h = BLOCK_SIZE;
}

int Fruit::GetRandomNumber(int maxNumber) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(1, maxNumber);
    return dist(rng);
}

void Fruit::UpdateTexture() {
    switch(type){
        case TYPE::APPLE:
            texture = TextureManager::GetInstance().GetTexture("appleTexture");
            break;
        case TYPE::BANANA:
            texture = TextureManager::GetInstance().GetTexture("bananaTexture");
            break;
        case TYPE::WATERMELON:
            texture = TextureManager::GetInstance().GetTexture("watermelonTexture");
            break;
    }
}

void Fruit::SetNewRandomTexture() {
    int randomNewFruit = GetRandomNumber(10);
    switch(randomNewFruit){
        case 1: case 2: case 3: case 4: case 5: // 50%
            type = TYPE::APPLE;
            break;
        case 6: case 7: case 8:  // 30%
            type = TYPE::BANANA;
            break;
        case 9: case 10:  // 20%
            type = TYPE::WATERMELON;
            break;
        default:
            break;
    }
    UpdateTexture();
}

bool Fruit::CheckFruitOnFruitCollision(SDL_Rect& potentialPosition) const {
    return std::ranges::any_of(MainState::GetInstance().GetFruitVector().begin(), MainState::GetInstance().GetFruitVector().end(), [&potentialPosition](const auto& fruit){
        return SDL_HasIntersection(&fruit->coords, &potentialPosition);
    });
}
