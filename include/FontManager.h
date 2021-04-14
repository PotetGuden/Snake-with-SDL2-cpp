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

    /*static FontManager &GetInstance(){
        static FontManager instance;
        return instance;
    }
    FontManager(FontManager const &) = delete;     // Copy Constructor
    FontManager(FontManager const &&) = delete;    // Move Constructor
    void operator = (FontManager const&) = delete;  // Likhetsoperator*/

    FontManager() = default;
    ~FontManager();
    void RenderFont(const std::string& text, SDL_Color textColor, bool isShaded, int x, int y, int w, int h);
    void SetFont();

private:

    std::string labelText;
    std::string labelFont;
    SDL_Color textColour{};
    SDL_Texture* labelTexture{};

    TTF_Font* gFont{};

    SDL_Rect position;

    //Image dimensions
    int mWidth{};
    int mHeight{};

    //SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);   // Henter inn w/h fra texture/image vi har lagd
    // SDL_Surface* surface = TTF_RenderText_Blended(fm->GetFont(font), text.c_str(), textColour);
};


#endif //SNAKE_FONTMANAGER_H
