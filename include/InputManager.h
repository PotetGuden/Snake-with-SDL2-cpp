//
// Created by Joste on 26.03.2021.
//

#ifndef SNAKE_INPUTMANAGER_H
#define SNAKE_INPUTMANAGER_H

#include <memory>
#include <SDL.h>

class InputManager{
public:
    static InputManager &GetInstance(){
        static InputManager instance;
        return instance;
    }
    // Sikrer at man ikke kan lage kopier ( aka singleton )
    InputManager(InputManager const &) = delete;     // Copy Constructor

    InputManager(InputManager const &&) = delete;    // Move Constructor

    void operator = (InputManager const&) = delete;  // Likhetsoperator

    void Update();
    //Keyboard
    bool KeyDown(int iKeyIndex) const;

    bool KeyStillDown(int iKeyIndex) const;

    bool KeyUp(int iKeyIndex) const;

    bool KeyStillUp(int iKeyIndex) const;

    //Mouse
    bool MouseDown(int iButton) const;

    bool MouseStillDown(int iButton) const;

    bool MouseUp(int iButton) const;

    bool MouseStillUp(int iButton) const;


    ~InputManager() = default;

private:
    InputManager();

    const Uint8* keys;

    std::unique_ptr<Uint8[]> oldKeys;

    int numKeys;

protected:

    int mouseX;

    int mouseY;

    Uint8 mouseButtons;

    Uint8 oldMouseButtons;
};
#endif //SNAKE_INPUTMANAGER_H
