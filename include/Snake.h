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

    void ChangeDirection(const Direction potentialDir, const Direction oppositeDir);
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
    bool CheckNewFruitCollisionSnake(SDL_Rect potentialPos);
    void CheckForCollisions(); // Kunne delt denne funksjon litt opp, men har valgt å ikke gjøre det.
    void StartWallCollisionThread();
private:

    // Storing copy of these here so we can use them for start position, initializing them in constructor
    SnakePart snakeHeadStart{},snakeBodyStart{},snakeTailStart{};
    std::vector<std::shared_ptr<SnakePart>> snakeBodyVector;
    std::shared_ptr<SnakePart> snakeHead = std::make_shared<SnakePart>();
    SnakePart prevPosition{}; // Kunne kanskje vært weak_ptr

    SDL_Rect SetSnakePartCoords(int x, int y);

    bool startPosition;
    int snakeSpeed;
    SDL_Rect headsNextMove;
    std::future<bool> isNextTileWall; // TODO LEGG DENNE SAMMEN MED DEN ANDRE COLLISION
    bool isAbleToChangeDirection = true; // Siden handle inputs kjører kjappere enn vi flytter snake head, så trenger vi å locke input når vi først ha endret direction
    // forklar hvorfor kollisjon sjekkene er i snake
};


#endif //SNAKE_SNAKE_H
