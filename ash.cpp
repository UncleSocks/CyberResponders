#include "./include/raylib.h"
#include <string>

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 500;
    const int fps = 60;
    const std::string windowTitle = "Ash Game";

    std::string windowText = "Testing window string for Raylib";

    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(fps);

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(windowText.c_str(), 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;


}