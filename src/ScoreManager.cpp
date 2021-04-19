//
// Created by Joste on 02.04.2021.
//

#include <fstream>
#include <iostream>
#include "../include/ScoreManager.h"
#include "../include/GameManager.h"

bool ScoreManager::GetScoresFromFile(const std::string& fileName, std::vector<int> &scoreVector) {
    if(!scoreVector.empty())
        scoreVector.erase(scoreVector.begin(), scoreVector.end());

    std::ifstream inputFile(fileName.c_str());

    if(!inputFile){
        std::cerr << "Cannot open the File: " << fileName << std::endl;
        return false;
    }

    int score;
    while (inputFile >> score){
        scoreVector.emplace_back(score);
    }

    inputFile.close();
    return true;
}

void ScoreManager::AddScore(const std::string& fileName, int currScore) {
    std::ofstream scoreFile;
    scoreFile.open(fileName, std::ios::app);
    if (scoreFile.is_open()) {
        scoreFile << currScore << std::endl;
        scoreFile.close();
    }
    scores.emplace_back(currScore);
    SortScores();
}

void ScoreManager::LoadScores() {
    if(!GetScoresFromFile("../scores/scores.txt", scores)){
        GameManager::GetInstance().gameRunning = false;
    };
}

int ScoreManager::GetHighScore() {
    return (!scores.empty()) ? scores.front() : 0;
}

void ScoreManager::SortScores() {
    if(!scores.empty()) {
        std::sort(scores.begin(), scores.end(), std::greater<>());
    }

    std::ofstream scoreFile("../scores/scores.txt");

    for(auto &score : scores) {
        scoreFile << score << std::endl;
    }

    scoreFile.close();
}
