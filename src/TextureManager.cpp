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
        SDL_DestroyRenderer(GameManager::renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface); // Legg til feilsjekk
    SDL_FreeSurface(surface);

    allTextures.insert(std::pair<const std::string&, SDL_Texture*>(textureName, texture));
}

TextureManager::~TextureManager() {
    /*for(auto& texture : allTextures){
        //std::cout << "Navn for: " << key << " Texture for: " << value << std::endl;
        SDL_DestroyTexture(texture.second);
        texture.second = nullptr;
    }*/
    std::ranges::for_each(allTextures.begin(), allTextures.end(), [](auto& texture){
        SDL_DestroyTexture(texture.second);
        texture.second = nullptr; // Just to be sure ref https://gamedev.stackexchange.com/questions/110891/do-i-need-to-delete-a-texture-after-calling-sdl-destroytexture second answer.
    });
}

SDL_Texture *TextureManager::GetTexture(const std::string &name) {
    return allTextures.find(name)->second;
}

void TextureManager::ReadTexturesFromFile() {
    std::ifstream file ("../Textures/textures.txt");

    if (file.is_open()){
        std::string line;
        while(getline(file, line)){
            //line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
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

