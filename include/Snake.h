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


class Snake {
public:
    enum class Direction {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    struct SnakePart : public GameObject {
        Direction partDirection;
    };

    static Snake &GetInstance(){
        static Snake instance;
        return instance;
    }

    ~Snake();
    Snake(Snake const &) = delete;     // Copy Constructor
    Snake(Snake const &&) = delete;    // Move Constructor
    void operator = (Snake const&) = delete;  // Likhetsoperator

    void ChangeDirection(Direction potentialDir, Direction oppositeDir);
    void MoveSnakeHead();
    void MoveBodyAndTail();

    void Update();
    void Render();
    void UpdateTexture();

    void Grow(int xTimes);
    void StopSnake();
    void StartPosition();

    SDL_Rect HeadsNextMove();
    Snake();
    bool CheckNewFruitCollisionSnake(SDL_Rect potentialPos) const;
    void CheckForCollisions();
    void StartWallCollisionThread();
private:
    // Storing copy of these here so we can use them for start position, initializing them in constructor
    SnakePart snakeHeadStart{},snakeBodyStart{},snakeTailStart{};
    SnakePart prevPosition{}; // Kunne kanskje vært weak_ptr

    std::shared_ptr<SnakePart> snakeHead = std::make_shared<SnakePart>();
    std::vector<std::shared_ptr<SnakePart>> snakeBodyVector;

    SDL_Rect SetSnakePartCoords(int x, int y);

    bool startPosition;
    int snakeSpeed;
    SDL_Rect headsNextMove;
    std::future<bool> isNextTileWall; // TODO LEGG DENNE SAMMEN MED DEN ANDRE COLLISION
    bool isAbleToChangeDirection = true; // Siden handle inputs kjører kjappere enn vi flytter snake head, så trenger vi å "locke" input når vi først har endret direction
};


#endif //SNAKE_SNAKE_H
