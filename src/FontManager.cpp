//
// Created by Joste on 01.04.2021.
//

#include <iostream>
#include "../include/FontManager.h"
#include "../include/GameManager.h"

void FontManager::RenderFont(const std::string& text, SDL_Color textColor, bool isShaded, int x, int y, int w, int h) {
    SDL_Surface* textSurface;

    //SDL_Color textColor = { 255, 255, 255 ,255};
    if(isShaded){
        textSurface = TTF_RenderText_Shaded( gFont, text.c_str(), textColor, SDL_Color{208,119,67} );
    } else{
        textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
    }

    if(gFont == nullptr) std::cout << "sikkert gFont som kodder" << std::endl;

    SDL_Texture* mTexture = SDL_CreateTextureFromSurface( GameManager::renderer, textSurface );

    position.x = x;
    position.y = y;
    position.w = w;
    position.h = h;
    if(SDL_RenderCopy(GameManager::renderer, mTexture, nullptr, &position) != 0){
        std::cout << "Far ikke lastet bilde" << std::endl;
    }
    SDL_FreeSurface( textSurface );

    SDL_DestroyTexture(mTexture); //VIKTIG

    //return mTexture;
}

FontManager::~FontManager() {
    std::cout << "Destructing Font Manager" << std::endl;
    //SDL_DestroyTexture(mTexture); //  usikker
}

void FontManager::SetFont() {
    gFont = TTF_OpenFont( "../fonts/Roboto-Regular.ttf", 50 );

}

