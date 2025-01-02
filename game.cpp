#include "game.h"

Game::Game() : m_turn(0)
{
    m_texture_map["grass"] = LoadTexture("assets/Grass.png");
    m_texture_map["water"] = LoadTexture("assets/Water.png");
    m_texture_map["city"] = LoadTexture("assets/City.png");
    m_texture_map["settler"] = LoadTexture("assets/Settler.png");

    m_city_names.push_back("ABC");
    m_city_names.push_back("DEF");
    m_city_names.push_back("GHI");

    m_next_city_name_idx = 0;
}

// Texture2D Game::get_texture(std::string k)
// {
//     m_texture_map.find(k);
// }

int Game::turn() { return m_turn; }

void Game::next_turn() { m_turn++; }

std::string Game::get_next_city_name()
{
    if (m_next_city_name_idx < m_city_names.size())
    {
        return m_city_names.at(m_next_city_name_idx++);
    }
    return "ERROR";
}
