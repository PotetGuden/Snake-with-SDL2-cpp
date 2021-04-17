//
// Created by Joste on 16.04.2021.
//

#include <iostream>
#include "../include/AudioManager.h"
#include "../include/GameManager.h"

AudioManager::AudioManager() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        GameManager::GetInstance().gameRunning = false;
    }
    SetSounds("crashSound", "../Audio/crash-to-wall.wav");
    SetSounds("eatingFruit", "../Audio/eating-fruit.wav");
    SetSounds("snakeEatingSnake", "../Audio/snake-eating-snake.wav");
    SetSounds("gameOver", "../Audio/game-over-sound-effect.wav");
    Mix_Volume(-1, 20);
}

void AudioManager::SetSounds(const std::string& soundName, const std::string& filePath) {

    auto sound = Mix_LoadWAV( filePath.c_str() );

    if( sound == nullptr ){
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        GameManager::GetInstance().gameRunning = false;
    }
    sounds.insert(std::pair<std::string, Mix_Chunk*>(soundName, sound));
}

void AudioManager::PlaySound(const std::string& soundName) {
    Mix_PlayChannel( -1, sounds.find(soundName)->second, 0 );
}

void AudioManager::CleanAudio() {
    for(auto& sound : sounds){
        std::cout << "Freeing " << sound.first << std::endl;
        Mix_FreeChunk( sound.second );
        sound.second = nullptr;
    }
}


