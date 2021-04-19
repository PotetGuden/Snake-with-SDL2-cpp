//
// Created by Joste on 27.03.2021.
//

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include <SDL.h>
#include <vector>
#include "GameObject.h"
#include <iostream>

class Map {
public:
    Map() = default;
    ~Map();

    static Map &GetInstance(){
        static Map instance;
        return instance;
    }
    Map(Map const &) = delete;   // Copy Constructor

    Map(Map const &&) = delete;    // Move Constructor

    void operator = (Map const&) = delete;  // Likhetsoperator

    bool LoadNextLevel(int lvl);

    bool CheckForWallCollision(SDL_Rect& nextPosition) const;

    void RenderMap() const;

private:

    void ReadMapFromFileIntoVector(std::string &filePath);

    void DeleteVectorContentIfNotEmpty();

    std::vector<std::string> mapFilePath = {
            "../maps/lvl1.txt",
            "../maps/lvl2.txt",
            "../maps/lvl3.txt"
    };

    std::vector<GameObject> wallTiles;

    std::vector<GameObject> grassTiles;
};


#endif //SNAKE_MAP_H
