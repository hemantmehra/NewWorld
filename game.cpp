#include "game.h"

Game::Game() : m_turn(0)
{
    m_texture_map["grass"] = LoadTexture("assets/Grass.png");
    m_texture_map["water"] = LoadTexture("assets/Water.png");
    m_texture_map["city"] = LoadTexture("assets/City.png");
    m_texture_map["settler"] = LoadTexture("assets/Settler.png");
}

// Texture2D Game::get_texture(std::string k)
// {
//     m_texture_map.find(k);
// }

int Game::turn() { return m_turn; }

void Game::next_turn() { m_turn++; }
