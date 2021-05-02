#include "raylib.h"
#include <time.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void show_huguin(bool playerMoving, AsepriteTag *moving, AsepriteTag *standing, int direction, Vector2 playerPosition, float scale){
    if (playerMoving) {
        DrawAsepriteTagEx(moving[direction], playerPosition, 0, scale, WHITE);
    }
    else {
        DrawAsepriteTagEx(standing[direction], playerPosition, 0, scale, WHITE);
    }
}

void show_boss(bool bossMoving, AsepriteTag *movingBoss, AsepriteTag *standingBoss, int directionBoss, Vector2 bossPosition, float scale){
    if (bossMoving) {
        DrawAsepriteTagEx(movingBoss[directionBoss], bossPosition, 0, scale, WHITE);
    }
    else {
        DrawAsepriteTagEx(standingBoss[directionBoss], bossPosition, 0, scale, WHITE);
    }
}

int main(void){

    const int screenWidth = 800;
    const int screenHeight = 850;
    SetTargetFPS(60);
    // Vector2 mousePoint = { 0.0f, 0.0f };
    
    InitWindow(screenWidth, screenHeight, "Fuja da Area II");
    InitAudioDevice();

    Music music = LoadMusicStream("./assets/horror_song.mp3");
    PlayMusicStream(music);
    SetMasterVolume(0.2f);

    Texture2D texture = LoadTexture("./assets/sprites/comeco.png");
    Aseprite room1 = LoadAseprite("./assets/sprites/room1.aseprite");
    Aseprite room2 = LoadAseprite("./assets/sprites/room2.aseprite");
    Aseprite room3 = LoadAseprite("./assets/sprites/room3.aseprite");
    // Aseprite room4 = LoadAseprite("./assets/sprites/room4.aseprite");
    // Aseprite room5 = LoadAseprite("./assets/sprites/room5.aseprite");
    // Aseprite room6 = LoadAseprite("./assets/sprites/room6.aseprite");
    // Aseprite room7 = LoadAseprite("./assets/sprites/room4.aseprite");

    Aseprite huguin = LoadAseprite("assets/huguin/huguin_andando.aseprite");
    Aseprite boss = LoadAseprite("assets/huguin/mob_andando.aseprite");

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

   AsepriteTag standingBoss[4] = {
        LoadAsepriteTag(boss, "paradoCima"),
        LoadAsepriteTag(boss, "paradoDireita"),
        LoadAsepriteTag(boss, "paradoBaixo"),
        LoadAsepriteTag(boss, "paradoEsquerda")
    };
    
    AsepriteTag movingBoss[4] = {
        LoadAsepriteTag(boss, "andarCima"),
        LoadAsepriteTag(boss, "andarDireita"),
        LoadAsepriteTag(boss, "andarBaixo"),
        LoadAsepriteTag(boss, "andarEsquerda")
   };

    int direction = 2;
    int directionBoss = 1;
    const float scale = 1;
    Vector2 playerPosition = {
        GetScreenWidth() / 5  - GetAsepriteWidth(huguin) / 5 * scale,
        GetScreenHeight() / 1.5   - GetAsepriteHeight(huguin) / 1.5 * scale
    };
    
    Vector2 bossPosition = {
        GetScreenWidth() / 1  - GetAsepriteWidth(boss) / 1 * scale,
        GetScreenHeight() / 5   - GetAsepriteHeight(boss) / 5 * scale
    };

    const float speed = 2;
    const float speedBoss = 1.3;

    bool playerMoving;
    bool bossMoving;
    //int limt_top = 40;
    

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
            bossMoving   = true;
        }
        else if(IsKeyDown(KEY_D)){
            direction = 1;
            playerMoving = true;
            bossMoving   = true;
        }
        else if(IsKeyDown(KEY_S)){
            direction = 2;
            playerMoving = true;
            bossMoving   = true; 
        }
        else if(IsKeyDown(KEY_A)){
            direction = 3;
            playerMoving = true;
            bossMoving   = true;
        }
        else{
            playerMoving = false;
            bossMoving   = true;
        }

        if (playerMoving) {
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
            UpdateAsepriteTag(&moving[direction]);
        }

        //movimentação do boss
        if (bossPosition.y !=  playerPosition.y || bossPosition.x !=  playerPosition.x) {
            if(bossPosition.y < playerPosition.y){
                bossPosition.y += (speedBoss);
                //direction = 2;
                directionBoss = 2;
            }
            if(bossPosition.x > playerPosition.x){
                bossPosition.x -= (speedBoss);
                //direction = 3;
                directionBoss = 3;
            }
            if(bossPosition.y > playerPosition.y){
                bossPosition.y -= (speedBoss);
                //direction = 0;
                directionBoss = 0;
            }
            if(bossPosition.x < playerPosition.x){
                bossPosition.x +=  speedBoss;
                //direction = 1;
                directionBoss = 1;
            }
            
            UpdateAsepriteTag(&movingBoss[directionBoss]);

        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            UpdateMusicStream(music);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
            
            //limitação de movimentção
            if(playerPosition.x <= 133){
                playerPosition.x = 133;
            }
            if(playerPosition.y <= 50){
                playerPosition.y = 50;
            }
            if(playerPosition.x >= 600){
                playerPosition.x = 600;
            }
            if(playerPosition.y >= 570){
                playerPosition.y = 570;
            }

            if (room_number==1){
                ClearBackground(RAYWHITE);
                DrawAseprite(room1, 0, 0, 0, WHITE);

                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                
                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=96){
                    room_number=2;
                    playerPosition.x=192;
                    playerPosition.y=610;
                }
                
                // if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                //     room_number = 2;
                // }
            }
            
            else if (room_number==2){
                ClearBackground(RAYWHITE);
                DrawAseprite(room2, 0, 0, 0, WHITE);
                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                show_boss(bossMoving, movingBoss, standingBoss, directionBoss, bossPosition, scale);
                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=96){
                    room_number=2;
                    playerPosition.x=192;
                    playerPosition.y=610;
                }
            }
            // 

            else if (room_number==3){
                ClearBackground(RAYWHITE);
                DrawAseprite(room3, 0, 0, 0, WHITE);

                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                // if((playerPosition.x>=317||playerPosition.x<=472)&&playerPosition.y==150){
                //     room_number=3;
                //     playerPosition.x=192;
                //     playerPosition.y=610;
                // }
                // playerPosition.x=192;
                // playerPosition.y=610;
                // delay(500);
                show_boss(bossMoving, movingBoss, standingBoss, directionBoss, bossPosition, scale);
                    
                
                if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                     room_number = 2;
                }

            }
                
            
            
            /*
            //534 x 534  133c 133b x 183e 183d

            Rectangle placa=DrawRectangle(int posX, int posY, int width, int height, BLANCK); //mensagem da placa
            if (CheckCollisionRecs("aseprite do huguinho", placa)){
               VER O TEXTO QUE VAI APARECER
            }   
            */
            
        EndDrawing();
    }
    
    UnloadAseprite(room1);
    UnloadAseprite(room2);
    UnloadAseprite(room3);
    UnloadAseprite(huguin);
    UnloadAseprite(boss);

    CloseAudioDevice();
    CloseWindow();
    // return 0;
}