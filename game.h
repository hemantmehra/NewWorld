#pragma once

#include <unordered_map>
#include <string>
#include <raylib.h>

class Game {
public:
    Game();
    Texture2D get_texture(std::string k);
    int turn();
    void next_turn();

private:
    int m_turn;
    std::unordered_map<std::string, Texture2D> m_texture_map;
};
