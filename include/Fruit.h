//
// Created by Joste on 26.03.2021.
//

#ifndef SNAKE_FRUIT_H
#define SNAKE_FRUIT_H


#include <SDL.h>
#include <string>
#include <memory>
#include "TextureManager.h"
#include "GameObject.h"

class Fruit : public GameObject {

public:
    enum class TYPE {
        APPLE,
        BANANA,
        WATERMELON
    };

    Fruit(TYPE fruit, int width, int height, int xPosition, int yPosition) : GameObject(xPosition,yPosition, width, height){
        type = fruit;
        UpdateTexture();
        isFruitEaten = false;
    }

    void UpdateTexture();

    void SetNewPosition();

    static int GetRandomNumber(int maxNumber);

    bool isFruitEaten;
    TYPE type;
private:
    SDL_Rect potentialFruitPos;
    SDL_Texture* appleTexture = TextureManager::GetInstance().LoadTexture("../images/AppleFruit.png");
    SDL_Texture* bananaTexture = TextureManager::GetInstance().LoadTexture("../images/Banana.png");
    SDL_Texture* watermelonTexture = TextureManager::GetInstance().LoadTexture("../images/Watermelon.png");

protected:
};


#endif //SNAKE_FRUIT_H
