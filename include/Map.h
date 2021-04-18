//
// Created by Joste on 27.03.2021.
//

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include <SDL.h>
#include <vector>
#include "GameObject.h"


class Map {
public:
    Map();
    ~Map();

    static Map &GetInstance(){
        static Map instance;
        return instance;
    }
    Map(Map const &) = delete;     // Copy Constructor
    Map(Map const &&) = delete;    // Move Constructor
    void operator = (Map const&) = delete;  // Likhetsoperator

    bool LoadNextLevel(int lvl);
    void ReadMapFromFileIntoVector(std::string &filePath);
    void DeleteVectorContentIfNotEmpty();

    bool CheckForWallCollision(SDL_Rect nextPosition);

    void RenderMap();

    std::vector<GameObject>& GetWallTiles();

private:
    std::vector<std::string> mapFilePath = {
            "../maps/lvl1.txt",
            "../maps/lvl2.txt",
            "../maps/lvl3.txt"
    };

    //int map[20][25];  // Each block is 32px * 32px / 20*32 = 640, 25*32 = 800 / Which is the window size snake is moving in
    //int tileType;

    std::vector<GameObject> wallTiles;
    std::vector<GameObject> grassTiles;
};


#endif //SNAKE_MAP_H
