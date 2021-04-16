//
// Created by Joste on 02.04.2021.
//

#include <fstream>
#include <iostream>
#include "../include/ScoreManager.h"

bool ScoreManager::GetScoresFromFile(const std::string& fileName, std::vector<int> &scoreVector) {

    std::ifstream inputFile(fileName.c_str());

    if(!inputFile){
        std::cerr << "Cannot open the File : "<< fileName << std::endl;
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
}

void ScoreManager::PrintScores() {
    bool result = GetScoresFromFile("../scores/scores.txt", scores);
    if(result){
        for(int &score : scores)
            std::cout << score << std::endl;
    }
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

std::vector<int> ScoreManager::GetScores() {
    return scores;
}
