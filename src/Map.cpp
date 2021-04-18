//
// Created by Joste on 27.03.2021.
//

#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include "../include/GameManager.h"


Map::Map(){

}


void Map::RenderMap() const {
    for(auto& wallObject : wallTiles){
        wallObject.Render();
    }
    for(auto& grassObject : grassTiles){
        grassObject.Render();
    }
}

Map::~Map() {
    std::cout << "DESTROYING MAP" << std::endl;
}

bool Map::CheckForWallCollision(SDL_Rect nextPosition) {
    for(auto &wallTile : wallTiles){
        if(nextPosition.x == wallTile.coords.x && nextPosition.y == wallTile.coords.y){
            return true;
        }
    }
    return false;
}

bool Map::LoadNextLevel(int lvl) {
    if(lvl > mapFilePath.size()){
        return false;
    }
    ReadMapFromFileIntoVector(mapFilePath[lvl]);
    return true;
}

std::vector<GameObject>& Map::GetWallTiles() {
    return wallTiles;
}

void Map::ReadMapFromFileIntoVector(std::string &filePath) {
    DeleteVectorContentIfNotEmpty();
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Unable to open map" << std::endl;
    }
    SDL_Rect dest;
    dest.w = dest.h = BLOCK_SIZE;

    int convertFileContentToInt;
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            dest.x = column * BLOCK_SIZE;
            dest.y = row * BLOCK_SIZE + 160;
            file >> convertFileContentToInt;
            if(convertFileContentToInt == 0){
                grassTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().GetTexture("grassTexture"));
            } else if(convertFileContentToInt == 1){
                wallTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().GetTexture("wallTexture"));
            }
        }
    }
}

void Map::DeleteVectorContentIfNotEmpty() {
    if(!wallTiles.empty()){
        wallTiles.erase(wallTiles.begin(), wallTiles.end());
    }
    if(!grassTiles.empty()){
        grassTiles.erase(grassTiles.begin(), grassTiles.end());
    }

}
