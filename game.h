#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <raylib.h>
#include "settlement.h"
#include "unit.h"
#include "tile.h"

class Game {
public:
    Game(int rows, int cols, int map_title_size, std::vector<Settlement*> *settlement_vec);
    // ~Game();
    void Unload();
    Texture2D get_texture(std::string k);
    int turn();
    void next_turn(std::vector<Settlement*> *city_vec);
    std::string get_next_city_name();
    void draw_map();
    void draw_settlement(std::vector<Settlement*> *city_vec);
    void draw_unit(Unit* unit);
    void draw_current_unit(Unit* current_unit, bool visible);
    void draw_rest_units(std::vector<Unit*> *unit_vec, Unit* current_unit);
    Unit *current_unit();
    Settlement *current_city();
    void set_current_unit(Unit *unit);
    void set_current_city(Settlement *city);

private:
    int m_turn;
    std::unordered_map<std::string, Texture2D> m_texture_map;
    std::vector<std::string> m_city_names;
    int m_next_city_name_idx;
    int m_rows;
    int m_cols;
    int m_map_title_size;
    int m_map[50][50];
    Settlement *m_current_city;
    Unit *m_current_unit;
};
