// #include "raylib.h"

// int main()
// {
// Texture2D huguin = LoadTexture("./assets/sprites/huguin.png");
// Vector2 position  = { 350.0f, 280.0f };
// Rectangle frameRec = { 0.0f, 0.0f, (float)huguin.width/3, (float)huguin.height};
// int currentFrame = 0;

// int framesSpeed = 5;
// int frameCounter = 0;

// SetTargetFPS(60);

// while (!WindowShouldClose())
// {
//         frameCounter++;

//         if (frameCounter >= (60/framesSpeed))
//         {
//             frameCounter = 0;
//             currentFrame++;

//             if (currentFrame > 2) currentFrame = 0;

//             frameRec.x = (float)currentFrame*(float)huguin.width/3;
//         }
//         BeginDrawing();

//             ClearBackground(RAYWHITE);
//             DrawTextureRec(huguin, frameRec, position, WHITE);  // Draw part of the texture

//         EndDrawing();
// }

//     UnloadTexture(huguin);
//     CloseWindow();

//     return 0;

// }