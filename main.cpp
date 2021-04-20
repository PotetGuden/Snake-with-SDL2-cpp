#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL_main.h>
#include "include/GameManager.h"


int main() {
    GameManager::GetInstance().Init();
    GameManager::GetInstance().GameLoop();
    return 0;
}
