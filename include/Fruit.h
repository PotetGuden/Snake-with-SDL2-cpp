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
    }

    void SetNewPosition();

    bool CheckFruitOnFruitCollision(SDL_Rect& potentialPosition) const;

    TYPE type;

    ~Fruit() = default;

private:
    int GetRandomNumber(int maxNumber);

    void SetNewRandomTexture();

    void UpdateTexture();

};


#endif //SNAKE_FRUIT_H
