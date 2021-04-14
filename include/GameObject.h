//
// Created by Joste on 05.04.2021.
//

#ifndef SNAKE_GAMEOBJECT_H
#define SNAKE_GAMEOBJECT_H


#include <SDL.h>

class GameObject {
public: // TODO Sett variabler i cpp filen istedenfor
    GameObject() = default;
    GameObject(int x, int y, int w, int h){
        coords.x = x;
        coords.y = y;
        coords.w = w;
        coords.h = h;
    }
    GameObject(int x, int y, int w, int h, SDL_Texture* texture){ // TEST
        coords.x = x;
        coords.y = y;
        coords.w = w;
        coords.h = h;
        this->texture = texture;
    }

    ~GameObject();

    void Render();
    SDL_Texture* texture;
    SDL_Rect coords;
    double angleTextureFlip = 0;
    SDL_RendererFlip renderFlip = SDL_FLIP_NONE; // Standard
};


#endif //SNAKE_GAMEOBJECT_H
