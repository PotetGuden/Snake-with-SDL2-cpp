//
// Created by Joste on 16.04.2021.
//

#ifndef SNAKE_AUDIOMANAGER_H
#define SNAKE_AUDIOMANAGER_H

#include <SDL_mixer.h>
#include <map>
#include <string>

class AudioManager {
public:
    static AudioManager &GetInstance(){
        static AudioManager instance;
        return instance;
    }

    ~AudioManager() = default;
    AudioManager(AudioManager const &) = delete;     // Copy Constructor
    AudioManager(AudioManager const &&) = delete;    // Move Constructor
    void operator = (AudioManager const&) = delete;  // Likhetsoperator

    void PlaySound(const std::string& soundName);
    void CleanAudio();
private:
    void SetSounds(const std::string& soundName, const std::string& filePath);
    std::map<std::string, Mix_Chunk*> sounds;
    AudioManager();
};


#endif //SNAKE_AUDIOMANAGER_H
