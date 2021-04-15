//
// Created by Joste on 26.03.2021.
//

#ifndef SNAKE_TEXTUREMANAGER_H
#define SNAKE_TEXTUREMANAGER_H


#include <SDL.h>
#include <map>
#include <memory>


class TextureManager {
public:
    static TextureManager &GetInstance(){
        static TextureManager instance;
        return instance;
    }

    ~TextureManager();
    TextureManager(TextureManager const &) = delete;     // Copy Constructor
    TextureManager(TextureManager const &&) = delete;    // Move Constructor
    void operator = (TextureManager const&) = delete;  // Likhetsoperator

    SDL_Texture* LoadTexture(const char* fileName); // &?
    void Draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);

    void LoadTextures(const char* textureName, const char* fileName);

    std::map<std::string, SDL_Texture*> allTextures;

private:

    TextureManager() = default;
};

#endif //SNAKE_TEXTUREMANAGER_H
