#include <raylib.h>
#include <stdio.h>
#include <math.h>

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);

    const int screenWidth = 800, screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Fuja da Area II!");

    // Sound song = LoadSound("../assets/horror_song.mp3");
    // InitAudioDevice();
    // SetMasterVolume(0.2f);
    SetTargetFPS(60); // timing
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(100, 100, 100, 300, RED);
        
        EndDrawing;
    }
    // CloseAudioDevice();
    // CloseWindow();

}