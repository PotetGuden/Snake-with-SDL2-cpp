//
// Created by Joste on 26.03.2021.
//

#include "../include/Fruit.h"
#include "../include/GameManager.h"
#include <random>
#include <iostream>
// TODO Frukt kan treffe frukt, og walls


void Fruit::SetNewPosition() {
    // do-while?
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
    //TextureManager::GetInstance().TestFunction("Fruit");
    UpdateTexture();

    // x = 23, y = 18 because map size is [25][20] and we take -1 for each side (top/bottom) (left/right)
    int x = GetRandomNumber(23)*BLOCK_SIZE;
    int y = GetRandomNumber(18)*BLOCK_SIZE+160;

    potentialFruitPos.w = BLOCK_SIZE;
    potentialFruitPos.h = BLOCK_SIZE;
    potentialFruitPos.x = x;
    potentialFruitPos.y = y;

    //while(Snake::GetInstance().CheckNewFruitCollisionSnake(x,y) || Map::GetInstance().CheckForWallCollision(possibleMove)){ TODO her
    while(Map::GetInstance().CheckForWallCollision(potentialFruitPos) || Snake::GetInstance().CheckNewFruitCollisionSnake(potentialFruitPos) ){
        x = GetRandomNumber(23)*BLOCK_SIZE;
        y = GetRandomNumber(18)*BLOCK_SIZE+160;
        potentialFruitPos.x = x;
        potentialFruitPos.y = y;
        std::cout << "Eple traff snake/vegg, lager nytt eple" << std::endl;
    }

    coords.x = x;
    coords.y = y;
    coords.w = BLOCK_SIZE;
    coords.h = BLOCK_SIZE;

    isFruitEaten = false;
    std::cout << "x: " << coords.x << " y: " << coords.y <<  " w: " << coords.w << " h: " << coords.h <<std::endl;
}

int Fruit::GetRandomNumber(int maxNumber) { //  https://codingnest.com/generating-random-numbers-using-c-standard-library-the-problems/
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(1, maxNumber);
    return dist(rng);
}

void Fruit::UpdateTexture() {
    switch(type){
        case TYPE::APPLE:
            texture = appleTexture;
            break;
        case TYPE::BANANA:
            texture = bananaTexture;
            break;
        case TYPE::WATERMELON:
            texture = watermelonTexture;
            break;
        default:
            break;
    }
}



/*Fruit::Fruit() {
    textureManager1 = std::make_unique<TextureManager>();
    appleTexture = textureManager1->LoadTexture("../images/AppleFruit.png");
    bananaTexture = textureManager1->LoadTexture("../images/Banana.png");
    watermelonTexture = textureManager1->LoadTexture("../images/Banana.png");

}*/


