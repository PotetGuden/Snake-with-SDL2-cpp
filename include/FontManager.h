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

    void operator = (FontManager const&) = delete;  // Likhetsoperator

    ~FontManager();

    void RenderFont(const std::string& text, SDL_Color textColor, bool isShaded, int x, int y, int w, int h);

    void SetFont();

private:

    TTF_Font* font = nullptr;

    FontManager() = default;

    SDL_Rect position{};

};


#endif //SNAKE_FONTMANAGER_H
