//
// Created by Joste on 01.04.2021.
//

#ifndef SNAKE_FONTMANAGER_H
#define SNAKE_FONTMANAGER_H


#include <SDL.h>
#include <string>
#include <SDL_ttf.h>



class FontManager {
public:

    static FontManager &GetInstance(){
        static FontManager instance;
        return instance;
    }
    FontManager(FontManager const &) = delete;     // Copy Constructor
    FontManager(FontManager const &&) = delete;    // Move Constructor
    void operator = (FontManager const&) = delete;  // Likhetsoperator*/

    ~FontManager();
    void RenderFont(const std::string& text, SDL_Color textColor, bool isShaded, int x, int y, int w, int h);
    void SetFont();
    TTF_Font* gFont = TTF_OpenFont( "../fonts/Roboto-Regular.ttf", 50 );


private:
    FontManager() = default;

    SDL_Rect position;

    //SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);   // Henter inn w/h fra texture/image vi har lagd
    // SDL_Surface* surface = TTF_RenderText_Blended(fm->GetFont(font), text.c_str(), textColour);
};


#endif //SNAKE_FONTMANAGER_H
