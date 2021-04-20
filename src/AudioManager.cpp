//
// Created by Joste on 16.04.2021.
//

#include <iostream>
#include <algorithm>
#include "../include/AudioManager.h"
#include "../include/GameManager.h"

AudioManager::AudioManager() :
    volume(10) {

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        GameManager::GetInstance().gameRunning = false;
    }
    SetSounds("crashSound", "../res/audio/crash-to-wall.wav");
    SetSounds("eatingFruit", "../res/audio/eating-fruit.wav");
    SetSounds("snakeEatingSnake", "../res/audio/snake-eating-snake.wav");
    SetSounds("gameOver", "../res/audio/game-over-sound-effect.wav");
    Mix_Volume(-1, volume);
}

void AudioManager::SetSounds(const std::string& soundName, const std::string& filePath) {

    auto sound = Mix_LoadWAV( filePath.c_str() );

    if( sound == nullptr ){
        std::cout << "Failed to load sound effect!" << std::endl;
        GameManager::GetInstance().gameRunning = false;
    }
    sounds.insert(std::pair<std::string, Mix_Chunk*>(soundName, sound));
}

void AudioManager::PlaySound(const std::string& soundName) {
    Mix_PlayChannel( -1, sounds.find(soundName)->second, 0 );
}

void AudioManager::CleanAudio() {
    /*for(auto& sound : sounds){
        Mix_FreeChunk( sound.second );
        sound.second = nullptr;
    }*/
    auto iter = sounds.begin();
    while (iter != sounds.end()) {
        Mix_FreeChunk( iter->second );
        iter->second = nullptr;
        ++iter;
    }

    // Just in case, since the SDL_Texture* is a part of a std::map
}

void AudioManager::MuteOrUnmuteSoundEffects() {
    volume = (volume == 10) ? 0 : 10;
    Mix_Volume(-1, volume);
}


