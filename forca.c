#include <stdio.h>
#include "raylib.h"

#define SW 1366
#define SH 768

typedef enum telas {
    MENU, 
    JOGO,
    TECLADO
}telas;

telas atual = JOGO;

int menu();

int main(){

    InitWindow(SW, SH, "Forca");

    SetTargetFPS(60);

    Texture2D quadro = LoadTexture("imagens/quadro.jpg");

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureEx(quadro, (Vector2){0,0}, 0.0, (float)SW / quadro.width, WHITE);

        char buffer[100];
        sprintf(buffer, "%d", (int)atual);
        DrawText(buffer, SW/ 2, SH / 2, 50, BLACK);

        for(int i = SW * 0.02; i < SW; i += SW * 0.05){
            DrawRectangle(i, 0, SW * 0.005, SH, BLUE);
        }

        for(int i = 0; i < SH; i += SH * 0.05){
            DrawRectangle(0, i, SW, SH * 0.005, RED);
        }

        EndDrawing();
    }

    UnloadTexture(quadro);
    CloseWindow();
}
