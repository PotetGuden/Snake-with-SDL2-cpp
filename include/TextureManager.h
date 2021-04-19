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


    void LoadTextures(const std::string& textureName,const std::string& fileName);
    SDL_Texture* GetTexture(const std::string& name);

    void ReadTexturesFromFile();

private:
    std::map<std::string, SDL_Texture*> allTextures;
    TextureManager() = default;
};

#endif //SNAKE_TEXTUREMANAGER_H
