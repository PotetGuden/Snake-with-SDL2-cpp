//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_STARTSTATE_H
#define SNAKE_STARTSTATE_H


#include <SDL.h>
#include "StateInterface.h"
#include "../GameObject.h"

class StartState : public StateInterface{
public:
    StartState();

    static StartState &GetInstance(){
        static StartState instance;
        return instance;
    }

    StartState(StartState const &) = delete;

    StartState(StartState const &&) = delete;

    void operator = (StartState const&) = delete;

    void HandleInputs() override;

    void Render() override;

private:

    int mouseXPos{};

    int mouseYPos{};

    std::unique_ptr<GameObject> snakeText;

    std::unique_ptr<GameObject> snakeBackground;

    std::unique_ptr<GameObject> playGameText;

    SDL_Color ruleTextColor{};

    bool showRules;
};


#endif //SNAKE_STARTSTATE_H
