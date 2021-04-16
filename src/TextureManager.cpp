//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include <fstream>

#include "../include/TextureManager.h"
#include "../include/GameManager.h"

// TODO legge all texture i en vector

SDL_Texture *TextureManager::LoadTexture(const std::string& fileName) {

    SDL_Surface* surface = IMG_Load(fileName.c_str());

    if(surface == nullptr){
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(GameManager::renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface); // Legg til feilsjekk
    SDL_FreeSurface(surface);

    return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect* src, SDL_Rect* dest) {
    SDL_RenderCopy(GameManager::renderer, texture, src, dest);

}

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
    for(auto &texture : allTextures){
        SDL_DestroyTexture(texture.second);
    }
}

SDL_Texture *TextureManager::GetTexture(const std::string &name) {
    std::cout << "Trying to get texture: " << allTextures.find(name)->first << std::endl;
    if(allTextures.find(name)->second == nullptr) std::cout << "texture = nullptr" << allTextures.find(name)->second << std::endl;
    return allTextures.find(name)->second;
}

bool TextureManager::TestFunction() {
    //std::map<std::string, SDL_Texture*> classTextures;

    std::ifstream textureConfigFile ("../Textures/textures.txt");
    if (textureConfigFile.is_open()){
        std::string line;
        while(getline(textureConfigFile, line)){
            //line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            if( line.empty() || line[0] == '#' )
                continue;

            std::size_t delimiterPos = line.find('=');
            std::string name = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            //auto value = "../images/game-states/start/SnakeStartBackground.png";

            std::cout << name << " " << value << std::endl;
            LoadTextures(name, value);
        }
    }
    else
        std::cerr << "Couldn't open config file for reading.\n";

    //return classTextures;
    return true;
}

