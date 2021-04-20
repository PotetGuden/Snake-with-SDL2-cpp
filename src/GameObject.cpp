//
// Created by Joste on 05.04.2021.
//

#include "../include/GameObject.h"
#include "../include/GameManager.h"


void GameObject::Render() const {
    SDL_RenderCopyEx(GameManager::GetInstance().renderer ,texture, nullptr, &coords, angleTextureFlip,nullptr, renderFlip);
}



