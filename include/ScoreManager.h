//
// Created by Joste on 02.04.2021.
//

#ifndef SNAKE_SCOREMANAGER_H
#define SNAKE_SCOREMANAGER_H


#include <vector>
#include <string>

class ScoreManager {
public:
    static ScoreManager &GetInstance(){
        static ScoreManager instance;
        return instance;
    }
    ScoreManager(ScoreManager const &) = delete;     // Copy Constructor
    ScoreManager(ScoreManager const &&) = delete;    // Move Constructor
    void operator = (ScoreManager const&) = delete;  // Likhetsoperator


    bool GetScoresFromFile(const std::string& fileName, std::vector<int> &scoreVector);
    void AddScore(const std::string& fileName, int currScore);
    void LoadScores();
    int GetHighScore();

    void SortScores();
private:
    ScoreManager() = default;
    std::vector<int> scores;
};


#endif //SNAKE_SCOREMANAGER_H
