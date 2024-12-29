#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CIV");
    Texture2D grass = LoadTexture("assets/Grass.png");
    Texture2D water = LoadTexture("assets/Water.png");
    Texture2D city = LoadTexture("assets/City.png");
    Texture2D settler = LoadTexture("assets/Settler.png");

    const int map_title_size = 32;
    const int rows = SCREEN_HEIGHT / map_title_size + 1;
    const int cols = SCREEN_WIDTH / map_title_size;

    int map[50][50];
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            map[i][j] = 1;
        }
    }
    int s_row = 10;
    int s_col = 10;

    while(!WindowShouldClose()) {
        if (IsKeyReleased(KEY_RIGHT)) s_col++;
        if (IsKeyReleased(KEY_LEFT)) s_col--;
        if (IsKeyReleased(KEY_UP)) s_row--;
        if (IsKeyReleased(KEY_DOWN)) s_row++;
        if (IsKeyReleased(KEY_B)) {
            map[s_row][s_col] = 2;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            for (int i=0; i<rows; i++) {
                for (int j=0; j<cols; j++) {
                    if (map[i][j] == 1) {
                        DrawTexture(grass, j*map_title_size, i*map_title_size, WHITE);
                    }
                    else if (map[i][j] == 0) {
                        DrawTexture(water, j*map_title_size, i*map_title_size, WHITE);
                    }
                    else if (map[i][j] == 2) {
                        DrawTexture(city, j*map_title_size, i*map_title_size, WHITE);
                    }
                }
            }

            DrawTexture(settler, s_col*map_title_size, s_row*map_title_size, WHITE);
        EndDrawing();
    }

    UnloadTexture(grass);
    UnloadTexture(water);
    UnloadTexture(city);

    CloseWindow();

    return 0;
}
