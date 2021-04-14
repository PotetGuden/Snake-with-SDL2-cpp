//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_MAINSTATE_H
#define SNAKE_MAINSTATE_H


#include <memory>
#include "../StateInterface.h"
#include "../GameObject.h"
#include "../ScoreManager.h"
#include "../Fruit.h"
#include "../FontManager.h"
#include "../Map.h"
#include "../Snake.h"
#include <future>


constexpr int BLOCK_SIZE = 32; // Modern c++ instead of #define

class MainState : public StateInterface{
public:
    MainState();
    static MainState &GetInstance(){
        static MainState instance;
        return instance;
    }

    //~MainState();
    MainState(MainState const &) = delete;     // Copy Constructor
    MainState(MainState const &&) = delete;    // Move Constructor
    void operator = (MainState const&) = delete;  // Likhetsoperator


    void Render() override;
    void Update();

    void AddScore(const int number);
    void ReduceLives();
    std::vector<std::shared_ptr<Fruit>> &GetFruitVector();
private:
    void GoToNextLvl();

    void HandleInputs();

    void RenderHeaderText();
    std::unique_ptr<GameObject> headerObject;
    int currentLvl;
    bool enableMovement;
    int frameCounterSpeed;
    int score;
    int timeLeft;
    int lives;
    bool showNextLvlMessage;
    int timer;
    int bonusScoreText;

    // Må lagre denne futuren selvom vi ikke bruker den, sånn at lifetimen til futuren vil vare
    // så lenge MainState gjør, og at main thread ikke venter på at denne skal bli "ferdig"
    std::future<void> dummyVariable;
protected:
    std::unique_ptr<ScoreManager> scoreManager;
    std::vector<std::shared_ptr<Fruit>> fruits;

    //std::unique_ptr<FontManager> fontManager;

    void AddThreeDifferentApples();
};


#endif //SNAKE_MAINSTATE_H
