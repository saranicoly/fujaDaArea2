// mob andando
/*

Aseprite boss = LoadAseprite("assets/huguin/mob_andando.aseprite");

AsepriteTag standingBoss[4] = {
        LoadAsepriteTag(boss, "paradoCima"),
        LoadAsepriteTag(boss, "paradoDireita"),
        LoadAsepriteTag(boss, "paradoBaixo"),
        LoadAsepriteTag(boss, "paradoEsquerda")
    };
    
    AsepriteTag movingBoss[4] = {
        LoadAsepriteTag(boss, "andarCima"),
        LoadAsepriteTag(boss,"andarDireita"),
        LoadAsepriteag(boss,"andarBaixo"),
        LoadAseriteTag(boss, "andarEsquerda")
   };

//while windowshouldclose

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

if (playerMoving) {
    DrawAsepriteTagEx(moving[direction], playerPosition, 0, scale, WHITE);
}
else {
    DrawAsepriteTagEx(standing[direction], playerPosition, 0, scale, WHITE);
} 
     */