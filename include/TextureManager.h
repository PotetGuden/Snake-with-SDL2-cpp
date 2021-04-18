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

    SDL_Texture* LoadTexture(const std::string& fileName); // &?
    void Draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);

    void LoadTextures(const std::string& textureName,const std::string& fileName);
    SDL_Texture* GetTexture(const std::string& name);

    bool TestFunction();

    std::map<std::string, SDL_Texture*> allTextures; // flytt til private
private:

    TextureManager() = default;
};

#endif //SNAKE_TEXTUREMANAGER_H
