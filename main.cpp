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

void draw_units(std::vector<Unit*> *unit_vec, Texture2D settler_texture, int map_title_size)
{
    for (auto unit : *unit_vec) {
        if (unit->is_alive()) {
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
    }
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
    UI_Type current_ui = UI_Map;

    Unit *settler_unit = new Unit(U_Settler, 10, 10);

    unit_vec.push_back(settler_unit);

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
        if (IsKeyReleased(KEY_RIGHT)) settler_unit->m_y++;
        if (IsKeyReleased(KEY_LEFT)) settler_unit->m_y--;
        if (IsKeyReleased(KEY_UP)) settler_unit->m_x--;
        if (IsKeyReleased(KEY_DOWN)) settler_unit->m_x++;
        if (IsKeyReleased(KEY_B)) {
            city_vec.push_back(new City(settler_unit->m_x, settler_unit->m_y));
            settler_unit->consume();
        }

        if (IsKeyReleased(KEY_Q)) {
            current_ui = UI_Map;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseX() / map_title_size;
            int my = GetMouseY() / map_title_size;

            for (auto city : city_vec) {
                if (city->m_x == mx && city->m_y == my) {
                    current_ui = UI_City;
                    current_city = city;
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
                    draw_units(&unit_vec, settler_texture, map_title_size);
                }
                break;

                case UI_City: {
                    DrawText("This is City UI", 0, 0, 24, WHITE);
                }
                break;
            }

            if (visible)
                DrawTexture(water_texture, 5*map_title_size, 5*map_title_size, WHITE);
        EndDrawing();
    }

    UnloadTexture(grass_texture);
    UnloadTexture(water_texture);
    UnloadTexture(city_texture);

    CloseWindow();

    return 0;
}
