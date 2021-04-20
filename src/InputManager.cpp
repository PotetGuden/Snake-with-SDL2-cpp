//
// Created by Joste on 26.03.2021.
//

#include <iostream>

#include "../include/InputManager.h"

bool InputManager::KeyDown(int iKeyIndex) const {
    return !oldKeys[iKeyIndex] && keys[iKeyIndex];
}

bool InputManager::KeyStillDown(int iKeyIndex) const {
    return oldKeys[iKeyIndex] && keys[iKeyIndex];
}

bool InputManager::KeyUp(int iKeyIndex) const {
    return oldKeys[iKeyIndex] && !keys[iKeyIndex];
}

bool InputManager::KeyStillUp(int iKeyIndex) const {
    return oldKeys[iKeyIndex] == keys[iKeyIndex]; // return !oldKeys[iKeyIndex] && !keys[iKeyIndex];
}

bool InputManager::MouseDown(int iButton) const {
    return (oldMouseButtons != mouseButtons) && (iButton == mouseButtons);
}

bool InputManager::MouseStillDown(int iButton) const{
    return (oldMouseButtons == mouseButtons) && (iButton == mouseButtons);
}

bool InputManager::MouseUp(int iButton) const {
    return (oldMouseButtons != mouseButtons) && (iButton == oldMouseButtons);
}

bool InputManager::MouseStillUp(int iButton) const {
    return (mouseButtons == oldMouseButtons) && (mouseButtons != iButton);
}

void InputManager::Update() {
    memcpy(oldKeys.get(), keys, static_cast<size_t>(numKeys));

    SDL_PumpEvents();

    oldMouseButtons = mouseButtons;
    mouseButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
}

InputManager::InputManager() {
    keys = SDL_GetKeyboardState(&numKeys);
    oldKeys = std::make_unique<Uint8[]>(static_cast<size_t>(numKeys));    //oldKeys = new Uint8[numKeys];
    memcpy(oldKeys.get(), keys, static_cast<size_t>(numKeys));

    std::cout << "Constructing InputManager " << std::endl;
}



