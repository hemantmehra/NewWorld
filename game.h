#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <raylib.h>

class Game {
public:
    Game();
    Texture2D get_texture(std::string k);
    int turn();
    void next_turn();
    std::string get_next_city_name();

private:
    int m_turn;
    std::unordered_map<std::string, Texture2D> m_texture_map;
    std::vector<std::string> m_city_names;
    int m_next_city_name_idx;
};
