#include <vector>
#include <assert.h>
#include <raylib.h>
#include "city.h"
#include "unit.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CIV");
    Texture2D grass_texture = LoadTexture("assets/Grass.png");
    Texture2D water_texture= LoadTexture("assets/Water.png");
    Texture2D city_texture = LoadTexture("assets/City.png");
    Texture2D settler_texture = LoadTexture("assets/Settler.png");

    std::vector<Unit*> unit_vec;
    std::vector<City*> city_vec;

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

    while(!WindowShouldClose()) {
        if (IsKeyReleased(KEY_RIGHT)) settler_unit->m_y++;
        if (IsKeyReleased(KEY_LEFT)) settler_unit->m_y--;
        if (IsKeyReleased(KEY_UP)) settler_unit->m_x--;
        if (IsKeyReleased(KEY_DOWN)) settler_unit->m_x++;
        if (IsKeyReleased(KEY_B)) {
            city_vec.push_back(new City(settler_unit->m_x, settler_unit->m_y));
            settler_unit->consume();
        }

        BeginDrawing();
            ClearBackground(BLACK);
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

            for (auto city : city_vec) {
                DrawTexture(city_texture, city->m_y*map_title_size, city->m_x*map_title_size, WHITE);
            }

            for (auto unit : unit_vec) {
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

        EndDrawing();
    }

    UnloadTexture(grass_texture);
    UnloadTexture(water_texture);
    UnloadTexture(city_texture);

    CloseWindow();

    return 0;
}
