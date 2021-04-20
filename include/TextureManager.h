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

    TextureManager() = default;

    ~TextureManager();

    TextureManager(TextureManager const &) = delete;

    TextureManager(TextureManager const &&) = delete;

    void operator = (TextureManager const&) = delete;

    SDL_Texture* GetTexture(const std::string& name);

    void ReadTexturesFromFile();

private:
    void LoadTextures(const std::string& textureName, const std::string& fileName);

    std::map<std::string, SDL_Texture*> allTextures;
};

#endif //SNAKE_TEXTUREMANAGER_H
