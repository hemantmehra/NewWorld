#include <vector>
#include <assert.h>
#include <iostream>
#include <raylib.h>
#include "city.h"
#include "unit.h"
#include "game.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum UI_Type {
    UI_Map,
    UI_City
};

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

    const int map_title_size = 32;
    const int rows = SCREEN_HEIGHT / map_title_size + 1;
    const int cols = SCREEN_WIDTH / map_title_size - 10;

    Game game(rows, cols, map_title_size);

    std::vector<Unit*> unit_vec;
    std::vector<City*> city_vec;
    City *current_city;
    Unit *current_unit;
    UI_Type current_ui = UI_Map;

    Unit *settler_unit = new Unit(U_Settler, 10, 10);
    Unit *settler_unit1 = new Unit(U_Warrior, 10, 10);

    unit_vec.push_back(settler_unit);
    unit_vec.push_back(settler_unit1);

    current_unit = unit_vec.at(0);

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
                std::string city_name = game.get_next_city_name();
                city_vec.push_back(new City(city_name, current_unit->m_x, current_unit->m_y));
                std::cout << "[city] " << city_name << " " << current_unit->m_x << ", " << current_unit->m_y << std::endl;
                current_unit->consume();
                current_unit = get_next_unit(&unit_vec, current_unit);
            }
        }

        if (IsKeyReleased(KEY_Q)) {
            current_ui = UI_Map;
        }

        if (IsKeyReleased(KEY_ENTER)) {
            game.next_turn();
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseY() / map_title_size;
            int my = GetMouseX() / map_title_size;

            std::cout << "[select] " << mx << ", " << my << std::endl;
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
                    game.draw_map();
                    game.draw_cities(&city_vec);
                    game.draw_current_unit(current_unit, visible);
                    game.draw_rest_units(&unit_vec, current_unit);
                }
                break;

                case UI_City: {
                    DrawText(TextFormat("%s", current_city->name().c_str()), 10, 0, 24, WHITE);
                    int idx = 0;
                    for (auto task: current_city->tasks) {
                        DrawText(TextFormat("%s", CityTask_to_Str(task).c_str()), 10, 24 + 24 * (idx++), 24, BLUE);
                    }
                }
                break;
            }

            DrawText(TextFormat("Turn: %d", game.turn()), cols*map_title_size, 0, 24, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
