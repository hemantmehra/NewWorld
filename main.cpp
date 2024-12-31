#include <vector>
#include <assert.h>
#include <iostream>
#include <raylib.h>
#include "city.h"
#include "unit.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum UI_Type {
    UI_Map,
    UI_City
};

void draw_map(int rows, int cols, int map_title_size, Texture2D grass_texture, Texture2D water_texture, int map[50][50])
{
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (map[i][j] == 1) {
                DrawTexture(grass_texture, j*map_title_size, i*map_title_size, WHITE);
            }
            else if (map[i][j] == 0) {
                DrawTexture(water_texture, j*map_title_size, i*map_title_size, WHITE);
            }
        }
    }
}

void draw_cities(std::vector<City*> *city_vec, Texture2D city_texture, int map_title_size)
{
    for (auto city : *city_vec) {
        DrawTexture(city_texture, city->m_y*map_title_size, city->m_x*map_title_size, WHITE);
    }
}

void draw_unit(Unit* unit, Texture2D settler_texture, int map_title_size)
{
    switch(unit->type()) {
        case U_Settler:
            DrawTexture(
                settler_texture,
                unit->m_y*map_title_size,
                unit->m_x*map_title_size,
                WHITE
            );
            break;
        default:
            assert(false);
    }
}

void draw_current_unit(Unit* current_unit, Texture2D settler_texture, int map_title_size, bool visible)
{
    if (current_unit && visible)
    draw_unit(current_unit, settler_texture, map_title_size);
}

void draw_rest_units(std::vector<Unit*> *unit_vec, Unit* current_unit, Texture2D settler_texture, int map_title_size)
{
    for (auto unit : *unit_vec) {
        if (unit->is_alive() && unit != current_unit) {
            draw_unit(unit, settler_texture, map_title_size);
        }
    }
}

Unit* get_next_unit(std::vector<Unit*> *unit_vec, Unit* current_unit)
{
    for (auto unit : *unit_vec) {
        if (unit->is_alive() && unit != current_unit) {
            return unit;
        }
    }
    return NULL;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CIV");
    SetTargetFPS(30);
    Texture2D grass_texture = LoadTexture("assets/Grass.png");
    Texture2D water_texture= LoadTexture("assets/Water.png");
    Texture2D city_texture = LoadTexture("assets/City.png");
    Texture2D settler_texture = LoadTexture("assets/Settler.png");

    std::vector<Unit*> unit_vec;
    std::vector<City*> city_vec;
    City *current_city;
    Unit *current_unit;
    UI_Type current_ui = UI_Map;

    Unit *settler_unit = new Unit(U_Settler, 10, 10);
    Unit *settler_unit1 = new Unit(U_Settler, 10, 10);

    unit_vec.push_back(settler_unit);
    unit_vec.push_back(settler_unit1);

    current_unit = unit_vec.at(0);

    const int map_title_size = 32;
    const int rows = SCREEN_HEIGHT / map_title_size + 1;
    const int cols = SCREEN_WIDTH / map_title_size;

    int map[50][50];
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            map[i][j] = 1;
        }
    }

    int frame_counter = 0;
    const int frameDelay = 10;
    bool visible = true;

    while(!WindowShouldClose()) {
        if (IsKeyReleased(KEY_RIGHT)) {
            if (current_unit) current_unit->m_y++;
        }
        if (IsKeyReleased(KEY_LEFT)) {
            if (current_unit) current_unit->m_y--;
        }
        if (IsKeyReleased(KEY_UP)) {
            if (current_unit) current_unit->m_x--;
        }
        if (IsKeyReleased(KEY_DOWN)) {
            if (current_unit) current_unit->m_x++;
        }
        if (IsKeyReleased(KEY_B)) {
            if (current_unit && current_unit->is_settler()) {
                city_vec.push_back(new City(current_unit->m_x, current_unit->m_y));
                std::cout << "[city] " << current_unit->m_x << ", " << current_unit->m_y << std::endl;
                current_unit->consume();
                current_unit = get_next_unit(&unit_vec, current_unit);
            }
        }

        if (IsKeyReleased(KEY_Q)) {
            current_ui = UI_Map;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseY() / map_title_size;
            int my = GetMouseX() / map_title_size;

            std::cout << "[select] " << mx << ", " << my << std::endl;
            for (auto city : city_vec) {
                if (city->m_x == mx && city->m_y == my) {
                    current_ui = UI_City;
                    current_city = city;
                    // std::cout << "Found city\n";
                    break;
                }
            }
        }

        frame_counter++;
        if (frame_counter >= frameDelay) {
            frame_counter = 0;
            visible = !visible;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            switch(current_ui) {
                case UI_Map: {
                    draw_map(rows, cols, map_title_size, grass_texture, water_texture, map);
                    draw_cities(&city_vec, city_texture, map_title_size);
                    draw_current_unit(current_unit, settler_texture, map_title_size, visible);
                    draw_rest_units(&unit_vec, current_unit, settler_texture, map_title_size);
                }
                break;

                case UI_City: {
                    DrawText("This is City UI", 0, 0, 24, WHITE);
                }
                break;
            }

            // if (visible)
            //     DrawTexture(water_texture, 5*map_title_size, 5*map_title_size, WHITE);
        EndDrawing();
    }

    UnloadTexture(grass_texture);
    UnloadTexture(water_texture);
    UnloadTexture(city_texture);

    CloseWindow();

    return 0;
}
