#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

void loadSprites(){
    
}
int main(void){

    const int screenWidth = 800;
    const int screenHeight = 850;
    SetTargetFPS(60);
    // Vector2 mousePoint = { 0.0f, 0.0f };
    //vector2 boss = {.x=screenWidth/2, .y =screenHeight/2}; //meio do mapa
    InitWindow(screenWidth, screenHeight, "Fuja da Area II");
    InitAudioDevice();

    Music music = LoadMusicStream("./assets/horror_song.mp3");
    PlayMusicStream(music);

    Texture2D texture = LoadTexture("./assets/sprites/comeco.png");
    Aseprite room1 = LoadAseprite("./assets/sprites/room1.aseprite");
    // Aseprite room2 = LoadAseprite("./assets/sprites/room2.aseprite");
    // Aseprite room3 = LoadAseprite("./assets/sprites/room3.aseprite");
    // Aseprite room4 = LoadAseprite("./assets/sprites/room4.aseprite");
    // Aseprite room5 = LoadAseprite("./assets/sprites/room5.aseprite");
    // Aseprite room6 = LoadAseprite("./assets/sprites/room6.aseprite");
    // Aseprite room7 = LoadAseprite("./assets/sprites/room4.aseprite");

    Aseprite huguin = LoadAseprite("assets/huguin/huguin_andando.aseprite");

    AsepriteTag standing[4] = {
        LoadAsepriteTag(huguin, "paradoCima"),
        LoadAsepriteTag(huguin, "paradoDireita"),
        LoadAsepriteTag(huguin, "paradoBaixo"),
        LoadAsepriteTag(huguin, "paradoEsquerda")
    };
    
    AsepriteTag moving[4] = {
        LoadAsepriteTag(huguin, "andarCima"),
        LoadAsepriteTag(huguin,"andarDireita"),
        LoadAsepriteTag(huguin,"andarBaixo"),
        LoadAsepriteTag(huguin, "andarEsquerda")
   };

    int direction = 2;
    const float scale = 1;
    Vector2 playerPosition = {
        GetScreenWidth() / 4  - GetAsepriteWidth(huguin) / 4 * scale,
        GetScreenHeight() /   - GetAsepriteHeight(huguin) / 8 * scale
    };

    const float speed = 2;

    bool playerMoving;
    

    int room_number = 0;
    // Aseprite room = LoadAseprite("assets/sprites/comeco.aseprite");

    // Main game loop
    
    while (!WindowShouldClose()){  // Detect window close button or ESC key
        
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            room_number = 1;
        }

        if(IsKeyDown(KEY_W)){
                direction = 0;
                playerMoving = true;
            }
            else if(IsKeyDown(KEY_D)){
                direction = 1;
                playerMoving = true;
            }
            else if(IsKeyDown(KEY_S)){
                direction = 2;
                playerMoving = true; 
            }
            else if(IsKeyDown(KEY_A)){
                direction = 3;
                playerMoving = true;
            }
            else{
                playerMoving = false;
            }

            if (playerMoving) {
            UpdateAsepriteTag(&moving[direction]);

            // Move the player.
            switch (direction) {
                case 0:
                    playerPosition.y -= speed;
                break;
                case 1:
                    playerPosition.x += speed;
                break;
                case 2:
                    playerPosition.y += speed;
                break;
                case 3:
                    playerPosition.x -= speed;
                break;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            UpdateMusicStream(music);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
            
            if (room_number==1){
                ClearBackground(RAYWHITE);
                DrawAseprite(room1, 0, 0, 0, WHITE);
            }

            if (playerMoving) {
                DrawAsepriteTagEx(moving[direction], playerPosition, 0, scale, WHITE);
            }
            else {
                DrawAsepriteTagEx(standing[direction], playerPosition, 0, scale, WHITE);
            }   

            



    
            
            /*
            if(CheckCollisionRecs(playerPosition.x,playerPosition.y,boss.x,player.y)==0){
                if(boss.x==playerPosition.x){
                    boss.y=boss.y - 50.0f;
                }
                if(boss.y==playerPosition.y){
                    boss.x=boss.x - 50.0f;
                }
                else{
                    boss.x=boss.x-50.0f;
                    boss.y=boss.y-50.0f;
                }
            }
            else{
                DrawText("Irá ficar mais 1 periodo aqui",700,50,50,RED);
            }
            DrawTexturePro( 
                ????????,
                Rectangle{0,0,15,40},
                Rectangle{boss.x,boss.y,15,40},
                Vector2{0,0},0,RAYWHITE);       
            */

        EndDrawing();
    }

    UnloadAseprite(huguin);
    CloseAudioDevice();
    CloseWindow();                // Close window and OpenGL context
    // return 0;
}