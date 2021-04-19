//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_ENDSTATE_H
#define SNAKE_ENDSTATE_H


#include <memory>
#include "../GameObject.h"
#include "StateInterface.h"
#include "../FontManager.h"
#include "../ScoreManager.h"

class EndState : public StateInterface{
public:
    EndState();
    static EndState &GetInstance(){
        static EndState instance;
        return instance;
    }
    EndState(EndState const &) = delete;     // Copy Constructor

    EndState(EndState const &&) = delete;    // Move Constructor

    void operator = (EndState const&) = delete;  // Likhetsoperator

    void Render() override;

    void HandleInputs() override;

    void UpdateCurrentScore(int score);

private:
    std::unique_ptr<GameObject> endBackground;

    std::vector<int> scores;

    int currentScore{};

    int mouseXPos{}, mouseYPos{};

    SDL_Color playAgainColor{}, exitGameColor{};
};


#endif //SNAKE_ENDSTATE_H
