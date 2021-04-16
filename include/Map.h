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


    void LoadMap(int arr[20][25]);
    void DrawMap();

    bool CheckForWallCollision(SDL_Rect nextPosition);
    void LoadMapTest(std::string &filePath);
    bool LoadNextLevel(int lvl);
    void AddCurrentWallTilesToVector();


    std::vector<GameObject> GetWallTiles();

private:

    SDL_Rect src, dest;
    SDL_Texture* grass;

    SDL_Texture* wall;

    std::vector<std::string> mapFilePath = {
            "../maps/lvl1.txt",
            "../maps/lvl2.txt",
            "../maps/lvl3.txt"
    };

    int map[20][25];  // Each block is 32px * 32px / 20*32 = 640, 25*32 = 800 / Which is the window size snake is moving in
    int tileType;

    std::vector<GameObject> wallTiles;
    std::vector<GameObject> grassTiles;
};


#endif //SNAKE_MAP_H
