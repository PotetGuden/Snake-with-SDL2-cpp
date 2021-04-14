//
// Created by Joste on 02.04.2021.
//

#ifndef SNAKE_SCOREMANAGER_H
#define SNAKE_SCOREMANAGER_H


#include <vector>
#include <string>

class ScoreManager {
public:
    bool GetScoresFromFile(const std::string& fileName, std::vector<int> &scoreVector);
    void AddScore(const std::string& fileName, int currScore);
    void PrintScores();
    int GetHighScore();

    void SortScores();
    std::vector<int> GetScores();
private:
    std::vector<int> scores;


};


#endif //SNAKE_SCOREMANAGER_H
