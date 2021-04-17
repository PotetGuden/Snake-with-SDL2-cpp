//
// Created by Joste on 05.04.2021.
//

#include "../include/GameObject.h"
#include "../include/GameManager.h"

// TODO Loop igjennom gameobjects og destroy textures?
GameObject::~GameObject() {
    //SDL_DestroyTexture(texture);
}

void GameObject::Render() {
    //if(angleTextureFlip > 0){
        SDL_RenderCopyEx(GameManager::renderer ,texture, nullptr, &coords, angleTextureFlip,nullptr, renderFlip);
    //}else{
     //   SDL_RenderCopy(GameManager::renderer ,texture, nullptr, &coords);
    //}

}



