//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include <fstream>
#include <algorithm>

#include "../include/TextureManager.h"
#include "../include/GameManager.h"


void TextureManager::LoadTextures(const std::string& textureName,const std::string& fileName) {

    SDL_Surface* surface = IMG_Load(fileName.c_str());

    if(surface == nullptr){
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(GameManager::GetInstance().renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::GetInstance().renderer, surface);
    SDL_FreeSurface(surface);

    allTextures.insert(std::pair<std::string, SDL_Texture*>(textureName, texture));
}

TextureManager::~TextureManager() {
    std::ranges::for_each(allTextures.begin(), allTextures.end(), [](auto& texture){
        SDL_DestroyTexture(texture.second);
        texture.second = nullptr;  // Just in case, since the SDL_Texture* is a part of a std::map
    });
}

SDL_Texture *TextureManager::GetTexture(const std::string &name) {
    return allTextures.find(name)->second;
}

void TextureManager::ReadTexturesFromFile() {
    std::ifstream file ("../res/textures/textures.txt");

    if (file.is_open()){
        std::string line;
        while(getline(file, line)){
            if( line.empty() || line[0] == '#' )
                continue;

            std::size_t delimiterPos = line.find('=');
            std::string name = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            LoadTextures(name, value);
        }
    }
    else
        std::cout << "Couldn't open file." << std::endl;


}

