//
// Created by Joste on 26.03.2021.
//

#include <iostream>
#include <SDL_image.h>
#include "../include/TextureManager.h"
#include "../include/GameManager.h"

// TODO legge all texture i en vector

//static std::map<std::string, SDL_Texture *> allTextures;

SDL_Texture *TextureManager::LoadTexture(const char* fileName) {

    SDL_Surface* surface = IMG_Load(fileName);

    if(surface == nullptr){
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(GameManager::renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface); // Legg til feilsjekk
    SDL_FreeSurface(surface);

    std::string tmp = "hei";
    //allTextures.insert(std::pair<std::string, SDL_Texture*>(fileName, texture));
    return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect* src, SDL_Rect* dest) {
    SDL_RenderCopy(GameManager::renderer, texture, src, dest);
}

void TextureManager::LoadTextures(const std::string& textureName, const char* fileName) {

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

