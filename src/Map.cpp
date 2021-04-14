//
// Created by Joste on 27.03.2021.
//

#include <iostream>
#include <fstream>
#include "../include/Map.h"
#include "../include/TextureManager.h"
#include "../include/GameManager.h"


Map::Map() {
    grass = TextureManager::GetInstance().LoadTexture("../images/grass.png");
    wall = TextureManager::GetInstance().LoadTexture("../images/wall.png");

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
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            tileType = map[row][column];

            dest.x = column * BLOCK_SIZE;
            dest.y = row * BLOCK_SIZE + 160;

            switch(tileType){
                case 0:
                    TextureManager::GetInstance().Draw(grass, &src, &dest);
                    break;
                case 1:
                    TextureManager::GetInstance().Draw(wall, &src,&dest);
                    //for(auto &wall : wallTiles)
                      //  wall.Render();
                    //wallCoords.emplace_back(dest);
                    break;

            }
        }
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



void Map::MapTest() {

}

std::vector<GameObject> Map::GetWallTiles() {
    return wallTiles;
}

void Map::AddCurrentWallTilesToVector() {
    if(!wallTiles.empty()){
        std::cout << "Deleting "<< wallTiles.size() << " wall pieces" << std::endl;
        wallTiles.erase(wallTiles.begin(), wallTiles.end());
    }

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            dest.x = column * BLOCK_SIZE;
            dest.y = row * BLOCK_SIZE + 160;
            if(map[row][column] == 1){
                wallTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().LoadTexture("../images/wall.png"));
            } else if(map[row][column] == 0){
                grassTiles.emplace_back(dest.x,dest.y,dest.w,dest.h,TextureManager::GetInstance().LoadTexture("../images/wall.png"));
            }

        }
    }
    std::cout << "Added " << wallTiles.size() << " wall pieces" << std::endl;
}
