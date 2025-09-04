#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "visual.h"

// Variáveis globais
telas tela_atual = MENU;
bool mostrar_grades = false;

int main(){

    InitWindow(SW, SH, "Forca");

    SetTargetFPS(60);

    srand(time(NULL));

    char *palavra;

    // Carrega imagem de fundo
    Texture2D quadro = LoadTexture("imagens/quadro.jpg");

    // Carrega a fonte customizada
    Font fonte = carrega_fonte("fontes/Chalk_Board.ttf", 96);

    // Loop principal
    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha tela de fundo
        DrawTextureEx(quadro, (Vector2){0,0}, 0.0, (float)SW / quadro.width, WHITE);

        // Para Testes
        if(mostrar_grades){
            for(int i = 0; i < SW; i += SW * 0.1){
                DrawRectangle(i, 0, SW * 0.005, SH, BLUE);
            }

            for(int i = 0; i < SH; i += SH * 0.1){
                DrawRectangle(0, i, SW, SH * 0.005, RED);
            }
        }
        
        // Selecão de telas
        switch(tela_atual){

            default:
                menu(fonte, palavra);
                break;
        }

        EndDrawing();
    }

    UnloadFont(fonte);
    UnloadTexture(quadro);
    CloseWindow();
}


