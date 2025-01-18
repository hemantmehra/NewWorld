#include <vector>
#include <assert.h>
#include <iostream>
#include <raylib.h>
#include "settlement.h"
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

    std::vector<Unit*> unit_vec;
    std::vector<Settlement*> settlement_vec;
    Game game(rows, cols, map_title_size, &settlement_vec);

    UI_Type current_ui = UI_Map;

    Unit *settler_unit = new Unit(U_Settler, 10, 10);

    unit_vec.push_back(settler_unit);
    game.set_current_unit(unit_vec.at(0));

    int frame_counter = 0;
    const int frameDelay = 10;
    bool visible = true;

    while(!WindowShouldClose()) {
        if (IsKeyReleased(KEY_RIGHT)) {
            if (game.current_unit()) game.current_unit()->m_y++;
        }
        if (IsKeyReleased(KEY_LEFT)) {
            if (game.current_unit()) game.current_unit()->m_y--;
        }
        if (IsKeyReleased(KEY_UP)) {
            if (game.current_unit()) game.current_unit()->m_x--;
        }
        if (IsKeyReleased(KEY_DOWN)) {
            if (game.current_unit()) game.current_unit()->m_x++;
        }
        if (IsKeyReleased(KEY_B)) {
            if (game.current_unit() && game.current_unit()->is_settler()) {
                std::string city_name = game.get_next_city_name();
                settlement_vec.push_back(new Settlement(S_City, city_name, game.current_unit()->m_x, game.current_unit()->m_y));
                std::cout << "[city] " << city_name << " " << game.current_unit()->m_x << ", " << game.current_unit()->m_y << std::endl;
                Unit *warrior = new Unit(U_Warrior, game.current_unit()->m_x, game.current_unit()->m_y);
                unit_vec.push_back(warrior);
                game.current_unit()->consume();
                game.set_current_unit(get_next_unit(&unit_vec, game.current_unit()));

            }
        }

        if (IsKeyReleased(KEY_Q)) {
            current_ui = UI_Map;
        }

        if (IsKeyReleased(KEY_ENTER)) {
            game.next_turn(&settlement_vec);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int mx = GetMouseY() / map_title_size;
            int my = GetMouseX() / map_title_size;

            std::cout << "[select] " << mx << ", " << my << std::endl;
            for (auto city : settlement_vec) {
                if (city->m_x == mx && city->m_y == my) {
                    current_ui = UI_City;
                    game.set_current_city(city);
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
                    game.draw_settlement(&settlement_vec);
                    game.draw_current_unit(game.current_unit(), visible);
                    game.draw_rest_units(&unit_vec, game.current_unit());
                }
                break;

                case UI_City: {
                    DrawText(TextFormat("%s", game.current_city()->name().c_str()), 10, 0, 24, WHITE);
                    int idx = 0;
                    for (auto task: game.current_city()->tasks) {
                        DrawText(TextFormat("%s", CityTask_to_Str(task).c_str()), 10, 24 + 24 * (idx++), 24, BLUE);
                    }
                }
                break;
            }

            DrawText(TextFormat("Turn: %d", game.turn()), cols*map_title_size, 0, 24, WHITE);

        EndDrawing();
    }

    game.Unload();
    CloseWindow();

    return 0;
}
