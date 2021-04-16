//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_ENDSTATE_H
#define SNAKE_ENDSTATE_H


#include <memory>
#include "../GameObject.h"
#include "../StateInterface.h"
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
    void Update();

private:
    //std::shared_ptr<FontManager> fontManager;
    std::unique_ptr<GameObject> endBackground;
    std::unique_ptr<GameObject> playerScore;
    std::unique_ptr<GameObject> highScore;
    std::unique_ptr<ScoreManager> scoreManager;
    std::vector<int> scores;
};


#endif //SNAKE_ENDSTATE_H
