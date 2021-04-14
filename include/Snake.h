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
    // Legg til i en vector/map i TextureManager
    SDL_Texture* headTextureUp;
    SDL_Texture *headTextureDown;
    SDL_Texture *headTextureLeft;
    SDL_Texture *headTextureRight;
    SDL_Texture *bodyTextureLeftRight;
    SDL_Texture *bodyTextureUpDown;
    SDL_Texture *bodyTextureLeftUpDownRight;
    SDL_Texture *bodyTextureRightDownUpLeft;
    SDL_Texture *bodyTextureRightUpDownLeft;
    SDL_Texture *bodyTextureUpRightLeftDown;
    SDL_Texture *tailTextureUp;
    SDL_Texture *tailTextureDown;
    SDL_Texture *tailTextureRight;

    SDL_Texture *tailTextureLeft;

    SDL_Rect potentialPosition;

    //std::unique_ptr<TextureManager> textureManager = std::make_unique<TextureManager>(); // Bruk heller TextureManager::

    bool startPosition;
    int snakeSpeed;
    Direction directionWhenSnakeStopped;
    SDL_Rect headsNextMove;

    std::future<bool> isNextTileWall; // TODO LEGG DENNE SAMMEN MED DEN ANDRE COLLISION
};


#endif //SNAKE_SNAKE_H
