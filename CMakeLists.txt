cmake_minimum_required(VERSION 3.9)
project(Snake)
INCLUDE(FindPkgConfig)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(Snake main.cpp src/InputManager.cpp include/InputManager.h src/GameManager.cpp include/GameManager.h src/Snake.cpp include/Snake.h src/TextureManager.cpp include/TextureManager.h src/Fruit.cpp include/Fruit.h src/Map.cpp include/Map.h src/FontManager.cpp include/FontManager.h src/ScoreManager.cpp include/ScoreManager.h src/GameObject.cpp include/GameObject.h include/GameStates/StateInterface.h src/GameStates/StartState.cpp include/GameStates/StartState.h src/GameStates/MainState.cpp include/GameStates/MainState.h src/GameStates/EndState.cpp include/GameStates/EndState.h src/AudioManager.cpp include/AudioManager.h)
target_link_libraries(Snake ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})
