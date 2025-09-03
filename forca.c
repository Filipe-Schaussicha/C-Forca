#include <stdio.h>
#include "raylib.h"

#define SW 1366
#define SH 768

// Telas do jogo
typedef enum telas {
    MENU, 
    FORCA,
    TECLADO,
    FIM_JOGO
}telas;

telas tela_atual = MENU;
bool mostrar_grades = false;

int menu();
bool botao(Rectangle retangulo_maior, float porsentagem_retangulo_menor, char *texto, Color externo, Color interno, Color texto_cor);

int main(){

    InitWindow(SW, SH, "Forca");

    SetTargetFPS(60);

    // Carrega imagem de fundo
    Texture2D quadro = LoadTexture("imagens/quadro.jpg");

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
                menu();
                break;
        }

        EndDrawing();
    }

    UnloadTexture(quadro);
    CloseWindow();
}

int menu(){

    //DrawRectangle(SW / 2, SH / 2, 200, 100, (Color){255,255,255, 50});
    //DrawRectangle(SW / 2 + 25, SH / 2 + 25, 150, 50, (Color){255,255,255, 50});

    botao((Rectangle){SW / 2, SH / 2, 200, 100}, 0.1, "", BLACK, BLUE, WHITE);

    return 0;
}

bool botao(Rectangle retangulo_maior, float margin, char *texto, Color externo, Color interno, Color texto_cor){

    DrawRectangleRec(retangulo_maior, externo);

    float diferenca = retangulo_maior.height * margin;

    retangulo_maior.x += diferenca / 2;
    retangulo_maior.y += diferenca / 2;
    retangulo_maior.height -= diferenca;
    retangulo_maior.width -= diferenca;

    DrawRectangleRec(retangulo_maior, interno);

}