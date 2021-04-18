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

// TODO FRUIT ON FRUIT COLLISION

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
    }

    void UpdateTexture();

    void SetNewPosition();

    int GetRandomNumber(int maxNumber); // static?

    void SetNewRandomTexture();

    bool CheckFruitOnFruitCollision(SDL_Rect& potentialPosition);

    TYPE type;

    ~Fruit();
private:



protected:
};


#endif //SNAKE_FRUIT_H
