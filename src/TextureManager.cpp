//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>

#include "../include/TextureManager.h"
#include "../include/GameManager.h"

// TODO legge all texture i en vector

SDL_Texture *TextureManager::LoadTexture(const char* fileName) {

    SDL_Surface* surface = IMG_Load(fileName);

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

void TextureManager::LoadTextures(const char* textureName, const char* fileName) {

    SDL_Surface* surface = IMG_Load(fileName);

    if(surface == nullptr){
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(GameManager::renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface); // Legg til feilsjekk
    SDL_FreeSurface(surface);
    std::cout << "For map.insert()" << std::endl;
    // static std::map<std::string, SDL_Texture *> allTextures;
    allTextures.insert(std::pair<std::string, SDL_Texture*>(textureName, texture));
    std::cout << "Etter map.insert()" << std::endl;

}

TextureManager::~TextureManager() {
    for(auto &texture : allTextures){
        SDL_DestroyTexture(texture.second);
    }
}

/*std::map<std::string, SDL_Texture *>& TextureManager::TestFunction(const std::string& className) {
    std::map<std::string, SDL_Texture*> classTextures;

    std::ifstream textureConfigFile ("../Textures/textures.txt");
    if (textureConfigFile.is_open()){
        std::string line;
        while(getline(textureConfigFile, line)){
            //line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            if( line.empty() || line[0] == '#' )
                continue;

            auto delimiterPos = line.find('=');
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            if(name == className)
                std::cout << name << " " << value << '\n';
        }
    }
    else
        std::cerr << "Couldn't open config file for reading.\n";

    return classTextures;
}*/

