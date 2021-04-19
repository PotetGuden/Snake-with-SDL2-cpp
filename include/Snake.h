//
// Created by Joste on 26.03.2021.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <SDL.h>
#include <vector>
#include <memory>
#include "Fruit.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <future>
#include <SDL_mixer.h>
#include <iostream>


class Snake {
public:
    enum class Direction {
        UP, DOWN, LEFT, RIGHT
    };

    struct SnakePart : public GameObject {
        Direction partDirection{};
    };

    static Snake &GetInstance(){
        static Snake instance;
        return instance;
    }

    Snake();
    ~Snake() = default;

    Snake(Snake const &) = delete;     // Copy Constructor
    Snake(Snake const &&) = delete;    // Move Constructor
    void operator = (Snake const&) = delete;  // Likhetsoperator

    void ChangeDirection(Direction potentialDir, Direction oppositeDir);
    void Update();
    void Render();
    void StopSnake();

    void StartPosition();
    bool CheckNewFruitCollisionSnake(SDL_Rect& potentialPos) const;

private:
    void MoveSnakeHead();
    void MoveBodyAndTail();
    void UpdateTexture();
    void Grow(int xTimes);

    void CheckForCollisions();
    void StartWallCollisionThread();
    void UpdateHeadsNextMove();
    SnakePart prevPosition{};

    std::shared_ptr<SnakePart> snakeHead = std::make_shared<SnakePart>();
    std::vector<std::shared_ptr<SnakePart>> snakeBodyVector;

    void InitializeSnakePartsStartPosition();

    bool startPosition;
    int snakeSpeed;
    SDL_Rect headsNextMove{};
    std::future<bool> isNextTileWall;
    bool isAbleToChangeDirection; // Siden handle inputs kjører kjappere enn vi flytter snake head, så trenger vi å "locke" input når vi først har endret direction

    std::future<void> dummyVariable;
};


#endif //SNAKE_SNAKE_H
