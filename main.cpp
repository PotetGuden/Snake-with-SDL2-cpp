#define SDL_MAIN_HANDLED
#include <iostream>


#include <SDL_main.h>
#include "include/GameManager.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    GameManager::GetInstance().Init();
    GameManager::GetInstance().GameLoop();
    return 0;
}
