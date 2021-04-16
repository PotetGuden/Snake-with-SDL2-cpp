//
// Created by Joste on 27.03.2021.
//

#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include "../include/GameManager.h"


// TODO har wall/grass textures 2 ganger.. fixxxx

Map::Map() {
    grass = TextureManager::GetInstance().LoadTexture("../images/map-obstacle/grass.png");
    wall = TextureManager::GetInstance().LoadTexture("../images/map-obstacle/wall.png");

    //LoadMap(lvl1);
    //LoadMap(lvl2);
    src.x = src.y = 0;
    src.w = dest.w = BLOCK_SIZE;
    src.h = dest.h = BLOCK_SIZE;
    dest.x = dest.y = 0;

}

void Map::LoadMap(int arr[20][25]) {

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            map[row][column] = arr[row][column];
        }
    }

}

void Map::DrawMap() {
    for(auto& wallObject : wallTiles){
        wallObject.Render();
    }
    for(auto& grassObject : grassTiles){
        grassObject.Render();
    }
}

Map::~Map() {

}

bool Map::CheckForWallCollision(SDL_Rect nextPosition) {
    SDL_Rect tmp;
    tmp.w = BLOCK_SIZE;
    tmp.h = BLOCK_SIZE;
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            tmp.x = column * BLOCK_SIZE;
            tmp.y = row * BLOCK_SIZE + 160;

            tileType = map[row][column];
            if(tileType == 1){
                if(nextPosition.x == tmp.x && nextPosition.y == tmp.y){
                    return true;
                }
            }
        }
    }
    return false;
}

void Map::LoadMapTest(std::string &filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open map" << std::endl;
    }

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            file >> map[row][column];
        }
    }
}

bool Map::LoadNextLevel(int lvl) {
    std::cout << "load map" << std::endl;
    if(lvl > mapFilePath.size()){
        return false;
    }
    LoadMapTest(mapFilePath[lvl]);
    AddCurrentWallTilesToVector();
    return true;
}

std::vector<GameObject> Map::GetWallTiles() {
    return wallTiles;
}

void Map::AddCurrentWallTilesToVector() {
    if(!wallTiles.empty()){
        std::cout << "Deleting "<< wallTiles.size() << " wall pieces" << std::endl;
        wallTiles.erase(wallTiles.begin(), wallTiles.end());
    }
    if(!grassTiles.empty()){
        grassTiles.erase(grassTiles.begin(), grassTiles.end());
    }

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            dest.x = column * BLOCK_SIZE;
            dest.y = row * BLOCK_SIZE + 160;
            if(map[row][column] == 1){
                wallTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().GetTexture("wallTexture"));
            } else if(map[row][column] == 0){
                grassTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().GetTexture("grassTexture"));
            }

        }
    }
    std::cout << "Added " << wallTiles.size() << " wall pieces" << std::endl;
}
