#include <assert.h>
#include "game.h"

Game::Game(int rows, int cols, int map_title_size)
    : m_turn(0), m_rows(rows), m_cols(cols), m_map_title_size(map_title_size)
{
    m_texture_map["grass"] = LoadTexture("assets/Grass.png");
    m_texture_map["water"] = LoadTexture("assets/Water.png");
    m_texture_map["city"] = LoadTexture("assets/City.png");
    m_texture_map["settler"] = LoadTexture("assets/Settler.png");
    m_texture_map["warrior"] = LoadTexture("assets/Warrior.png");
    m_texture_map["river"] = LoadTexture("assets/River.png");
    m_texture_map["hill"] = LoadTexture("assets/Hill.png");

    m_city_names.push_back("ABC");
    m_city_names.push_back("DEF");
    m_city_names.push_back("GHI");

    m_next_city_name_idx = 0;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (i == 0 || j == 0 || i == rows-1 || j == cols-1)
                m_map[i][j] = T_SEA;
            else
                m_map[i][j] = T_GRASS;
        }
    }

    m_map[1][1] = T_HILL;
    m_map[1][2] = T_HILL;
    m_map[2][1] = T_HILL;
    m_map[2][2] = T_HILL;

    int x = GetRandomValue(rows/5, 4 * rows/5);
    int y1 = GetRandomValue(cols/5, cols/3);
    int y2 = GetRandomValue(2*cols/3, 4*cols/5);

    for (int i=y1; i<y2; i++) {
        m_map[x][i] = T_RIVER;
    }
}

void Game::Unload()
{
    for (auto& it : m_texture_map) {
        UnloadTexture(it.second);
    }
}

int Game::turn() { return m_turn; }

void Game::next_turn(std::vector<City*> *city_vec)
{
    m_turn++;
    for (auto city : *city_vec) {
        city->update_food_storage();
    }
}

std::string Game::get_next_city_name()
{
    if (m_next_city_name_idx < m_city_names.size())
    {
        return m_city_names.at(m_next_city_name_idx++);
    }
    return "ERROR";
}


void Game::draw_map()
{
    for (int i=0; i<m_rows; i++) {
        for (int j=0; j<m_cols; j++) {
            Texture2D t;
            switch(m_map[i][j]) {
                case T_GRASS:
                    t = m_texture_map["grass"];
                    break;
                case T_RIVER:
                    t = m_texture_map["river"];
                    break;
                case T_HILL:
                    t = m_texture_map["hill"];
                    break;
                default:
                    t = m_texture_map["water"];

            }
            DrawTexture(t, j*m_map_title_size, i*m_map_title_size, WHITE);
        }
    }
}

void Game::draw_cities(std::vector<City*> *city_vec)
{
    for (auto city : *city_vec) {
        DrawTexture(m_texture_map["city"], city->m_y*m_map_title_size, city->m_x*m_map_title_size, WHITE);
        DrawText(
            TextFormat("%d", city->population()),
            city->m_y*m_map_title_size + m_map_title_size/3,
            city->m_x*m_map_title_size + m_map_title_size/3,
            2 * m_map_title_size/3,
            WHITE
        );
    }
}

void Game::draw_unit(Unit* unit)
{
    switch(unit->type()) {
        case U_Settler:
            DrawTexture(
                m_texture_map["settler"],
                unit->m_y*m_map_title_size,
                unit->m_x*m_map_title_size,
                WHITE
            );
            break;
        case U_Warrior:
            DrawTexture(
                m_texture_map["warrior"],
                unit->m_y*m_map_title_size,
                unit->m_x*m_map_title_size,
                WHITE
            );
            break;
        default:
            assert(false);
    }
}

void Game::draw_current_unit(Unit* current_unit, bool visible)
{
    if (current_unit && visible)
    draw_unit(current_unit);
}

void Game::draw_rest_units(std::vector<Unit*> *unit_vec, Unit* current_unit)
{
    for (auto unit : *unit_vec) {
        if (unit->is_alive() && unit != current_unit) {
            draw_unit(unit);
        }
    }
}

Unit *Game::current_unit()
{
    return m_current_unit;
}

City *Game::current_city()
{
    return m_current_city;
}

void Game::set_current_unit(Unit *unit)
{
    m_current_unit = unit;
}

void Game::set_current_city(City *city)
{
    m_current_city = city;
}
