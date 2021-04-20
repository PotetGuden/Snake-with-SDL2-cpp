//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_MAINSTATE_H
#define SNAKE_MAINSTATE_H


#include <memory>
#include "StateInterface.h"
#include "../GameObject.h"
#include "../ScoreManager.h"
#include "../Fruit.h"
#include "../FontManager.h"
#include "../Map.h"
#include "../Snake.h"
#include <future>
#include <SDL_mixer.h>


constexpr int BLOCK_SIZE = 32; // Width and Height of each tile within the snakemap
constexpr int HEADER_TEXTURE_Y_OFFSET = 160;

class MainState : public StateInterface{
public:
    MainState();
    static MainState &GetInstance(){
        static MainState instance;
        return instance;
    }

    MainState(MainState const &) = delete;     // Copy Constructor

    MainState(MainState const &&) = delete;    // Move Constructor

    void operator = (MainState const&) = delete;  // Likhetsoperator

    void Render() override;

    void Update();

    void AddScore(const int& number);

    void ReduceLives();

    void RestartGame();

    std::vector<std::shared_ptr<Fruit>>& GetFruitVector();

private:
    void DecreaseSpeedOverTime();

    void GoToNextLvl();

    void HandleInputs() override;

    void RenderHeaderText() const;
    
    void RenderNextLvlMessage();

    std::unique_ptr<GameObject> headerObject; // probably nææt
    bool enableMovement;
    int currentLvl;
    int score;
    int animateBonusScoreText;
    int xTimesSlowerThenFPS;
    int timeLeft;
    int lives;
    bool showNextLvlMessage;

    std::vector<std::shared_ptr<Fruit>> fruits;
    void GameOver() const;
    int timerForNextLvLMessage;
    void AddThreeDifferentFruits();
};


#endif //SNAKE_MAINSTATE_H
