//
// Created by Joste on 05.04.2021.
//

#include "../include/GameObject.h"
#include "../include/GameManager.h"

// TODO Loop igjennom gameobjects og destroy textures?
GameObject::~GameObject() {

}

void GameObject::Render() const {
    SDL_RenderCopyEx(GameManager::renderer ,texture, nullptr, &coords, angleTextureFlip,nullptr, renderFlip);
}



