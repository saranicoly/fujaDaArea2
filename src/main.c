#include "raylib.h"

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include "raylib-aseprite.h"

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

int test_colision_boss(Vector2 playerPosition, Vector2 bossPosition){
    // return 0; //descomentar essa linha e comentar a condicional, caso queira desativar a colisão
    if ((playerPosition.x - bossPosition.x) <=1 && (playerPosition.y - bossPosition.y) <= 1){
        return 1;
    }
    else{
        return 0;
    }
}

int main(void){

    const int screenWidth = 800;
    const int screenHeight = 850;
    SetTargetFPS(60);
    
    InitWindow(screenWidth, screenHeight, "Fuja da Area II");
    InitAudioDevice();

    Music music = LoadMusicStream("./assets/horror_song.mp3");
    PlayMusicStream(music);
    SetMasterVolume(0.1f);

    Aseprite comeco = LoadAseprite("./assets/sprites/comeco.aseprite");
    Aseprite room1 = LoadAseprite("./assets/sprites/room1.aseprite");
    Aseprite room2 = LoadAseprite("./assets/sprites/room2.aseprite");
    Aseprite room3 = LoadAseprite("./assets/sprites/room3.aseprite");
    Aseprite room4 = LoadAseprite("./assets/sprites/room4.aseprite");
    Aseprite room5 = LoadAseprite("./assets/sprites/acm1.aseprite");
    Aseprite room6 = LoadAseprite("./assets/sprites/acm2.aseprite");
    Aseprite room7 = LoadAseprite("./assets/sprites/acm3.aseprite");

    Aseprite room8 = LoadAseprite("./assets/sprites/game_over.aseprite");

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
    int colision = 0;
    Vector2 playerPosition = {
        GetScreenWidth() / 5  - GetAsepriteWidth(huguin) / 5 * scale,
        GetScreenHeight() / 1.5   - GetAsepriteHeight(huguin) / 1.5 * scale
    };
    
    Vector2 bossPosition = {
        GetScreenWidth() / 1  - GetAsepriteWidth(boss) / 1 * scale,
        GetScreenHeight() / 5   - GetAsepriteHeight(boss) / 5 * scale
    };

    const float speed = 2;
    const float speedBoss = 1.1;

    bool playerMoving;
    bool bossMoving;    

    int room_number = 0;

    // Main game loop
    while (!WindowShouldClose()){  // Detect window close button or ESC key

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

        //andar boss
        if (bossPosition.y !=  playerPosition.y || bossPosition.x !=  playerPosition.x) {
            if(bossPosition.y < playerPosition.y){
                bossPosition.y += (speedBoss);
                directionBoss = 2;
            }
            if(bossPosition.x > playerPosition.x){
                bossPosition.x -= (speedBoss);
                directionBoss = 3;
            }
            if(bossPosition.y > playerPosition.y){
                bossPosition.y -= (speedBoss);
                directionBoss = 0;
            }
            if(bossPosition.x < playerPosition.x){
                bossPosition.x +=  speedBoss;
                directionBoss = 1;
            }
            
            UpdateAsepriteTag(&movingBoss[directionBoss]);

        }

        BeginDrawing();

            UpdateMusicStream(music);
            if(room_number==0){
                ClearBackground(RAYWHITE);
                DrawAseprite(comeco, 0, 0, 0, WHITE);
                DrawText("APERTE ESPAÇO E COMECE", screenWidth - 700, screenHeight - 315, 40, RED);
                DrawText("\n\nUSE 'W' 'A' 'S' 'D' PARA SE MOVIMENTAR", screenWidth - 750, screenHeight - 315, 34, RED);
                if(IsKeyPressed(KEY_SPACE)){
                    room_number=1;
                }
            }
            
            //paredes laterais
            //esquerda
            if(playerPosition.x <= 133){
                playerPosition.x = 133;
            }
            //cima
            if(playerPosition.y <= 50){
                playerPosition.y = 50;
            }
            //direita
            if(playerPosition.x >= 600){
                playerPosition.x = 600;
            }
            //baixo
            if(playerPosition.y >= 570){
                playerPosition.y = 570;
            }

            //troca de salas
            if (room_number==1){
                ClearBackground(RAYWHITE);
                DrawAseprite(room1, 0, 0, 0, WHITE);
                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                DrawText("\n\nVOCÊ SÓ TEM UMA VIDA\n   CUIDE BEM DELA!", screenWidth - 520, screenHeight - 738, 21, BLACK);
                
                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=96){
                    room_number=2;
                    playerPosition.x=192;
                    playerPosition.y=610;
                }
            }
            
            else if (room_number==2){
                ClearBackground(RAYWHITE);
                DrawAseprite(room2, 0, 0, 0, WHITE);
                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                show_boss(bossMoving, movingBoss, standingBoss, directionBoss, bossPosition, scale);
                
                colision = test_colision_boss(playerPosition, bossPosition);
                if (colision==1){
                    room_number = 8;
                }
                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=140){
                    room_number=3;
                    playerPosition.x=192;
                    playerPosition.y=610;
                }
            }
            else if (room_number==3){
                ClearBackground(RAYWHITE);
                DrawAseprite(room3, 0, 0, 0, WHITE);
                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                show_boss(bossMoving, movingBoss, standingBoss, directionBoss, bossPosition, scale);

                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=140){
                 room_number=4;
                     playerPosition.x=192;
                        playerPosition.y=610;
                     }
            }
            else if (room_number==4){
                ClearBackground(RAYWHITE);
                DrawAseprite(room4, 0, 0, 0, WHITE);
                show_huguin(playerMoving, moving, standing, direction, playerPosition, scale);
                show_boss(bossMoving, movingBoss, standingBoss, directionBoss, bossPosition, scale);

                if(playerPosition.x>=340&&playerPosition.x<=400&&playerPosition.y<=140){
                    room_number=5;
                    playerPosition.x=192;
                    playerPosition.y=610;
                }
                
            }
            else if (room_number==8){
                ClearBackground(RAYWHITE);
                DrawAseprite(room8, 0, 0, 0, WHITE);
                if(IsKeyPressed(KEY_SPACE)){
                    room_number=1;
                }

            }
             else if (room_number==5){
                ClearBackground(RAYWHITE);
                DrawAseprite(room5, 0, 0, 0, WHITE);
                DrawText("Meu deus! você conseguiu escapar da Área II\nSão poucos os que conseguem", screenWidth - 760, screenHeight - 290, 32, BLACK);

                DrawText("aperte 'espaço' para passar", screenWidth - 300, screenHeight - 120, 19, DARKGRAY);
                    if(IsKeyPressed(KEY_SPACE)){
                        room_number=6;
                    }
             }
            
            else if (room_number==6){
                ClearBackground(RAYWHITE);
                DrawAseprite(room6, 0, 0, 0, WHITE);
                DrawText("Mas não vem ao caso, que bom \nque você conseguiu!\nEscapar desse lugar não\n é tarefa fácil", screenWidth - 750, screenHeight - 290, 35, BLACK);
                DrawText("aperte 'espaço' para passar", screenWidth - 300, screenHeight - 120, 19, DARKGRAY);
                
                    if(IsKeyPressed(KEY_SPACE)){
                        room_number=7;
                    }
            }

            else if (room_number==7){
                ClearBackground(RAYWHITE);
                DrawAseprite(room7, 0, 0, 0, WHITE);
                DrawText("Vamos meu aluno, me acompanhe!\nVamos voltar para o CIn!", screenWidth - 700, screenHeight - 290, 40, BLACK);
                DrawText("aperte 'espaço' para finalizar", screenWidth - 300, screenHeight - 120, 19, DARKGRAY);
                    if(IsKeyPressed(KEY_SPACE)){
                        CloseWindow();
                    }
            }

        EndDrawing();
    }
    
    UnloadAseprite(room1);
    UnloadAseprite(room2);
    UnloadAseprite(room3);
    UnloadAseprite(room4);
    UnloadAseprite(room5);
    UnloadAseprite(room6);
    UnloadAseprite(room7);
    UnloadAseprite(room8);
    UnloadAseprite(huguin);
    UnloadAseprite(boss);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}