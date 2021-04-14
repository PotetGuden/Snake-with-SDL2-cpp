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

bool InputManager::MouseDown(int iButton) {
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

InputManager::~InputManager() {

}

void InputManager::Update() {
    memcpy(oldKeys.get(),keys,numKeys);

    SDL_PumpEvents();

    oldMouseButtons = mouseButtons;
    mouseButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);
}

InputManager::InputManager() {
    keys = SDL_GetKeyboardState(&numKeys);
    oldKeys = std::make_unique<Uint8[]>(numKeys);    //oldKeys = new Uint8[numKeys];
    memcpy(oldKeys.get(),keys,numKeys);

    std::cout << "Constructing InputManager " << std::endl;
}



