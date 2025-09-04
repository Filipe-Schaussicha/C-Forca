#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

// Variáveis globais
telas tela_atual = MENU;
bool mostrar_grades = false;
char palavra[1000] = "";

int menu(Font fonte);
bool botao(Rectangle retangulo_maior, float porsentagem_retangulo_menor, char *texto, Color externo, Color interno, Color texto_cor, Font fonte);
void escolher_palavra_aleatoria(int dificuldade);
float centro_x_texto(char *texto, int centro, int tamanho_fonte, Font fonte);

int main(){

    InitWindow(SW, SH, "Forca");

    SetTargetFPS(60);

    srand(time(NULL));

    // Carrega imagem de fundo
    Texture2D quadro = LoadTexture("imagens/quadro.jpg");

    // Carrega todas as letras possíveis da fonte
    int chars[] = {
    // Letras maiúsculas
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'Á','À','Â','Ã','É','Ê','Í','Ó','Ô','Õ','Ú','Ç',
    
    // Letras minúsculas
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    'á','à','â','ã','é','ê','í','ó','ô','õ','ú','ç',
    
    // Números
    '0','1','2','3','4','5','6','7','8','9',
    
    // Pontuação e símbolos ASCII comuns
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
    ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~',
    
    // Espaço
    ' '
    };
    int charCount = sizeof(chars)/sizeof(chars[0]);

    // Carrega a fonte customizada
    Font fonte = LoadFontEx("fontes/Chalk_Board.ttf", 96, chars, charCount);

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
                menu(fonte);
                break;
        }

        EndDrawing();
    }

    UnloadFont(fonte);
    UnloadTexture(quadro);
    CloseWindow();
}

int menu(Font fonte){

    int dificuldade = 0;

    // Variáveis de referência para ajudar no possicionamento
    float coluna = SW * 0.1;
    float row = SH * 0.1;
    float margin = row * 0.1;

    //DrawRectangle(SW / 2, SH / 2, 200, 100, (Color){255,255,255, 50});
    //DrawRectangle(SW / 2 + 25, SH / 2 + 25, 150, 50, (Color){255,255,255, 50});

    // Escrita dos títulos
    DrawTextEx(fonte, "Bem-vindo ao C-Forca!", (Vector2){centro_x_texto("Bem-vindo ao C-Forca!", SW / 2, 128, fonte), row * 2.5 + margin}, 128 , 2 ,WHITE);

    DrawTextEx(fonte, "Escolha uma das dificuldades", (Vector2){centro_x_texto("Escolha uma das dificuldades", SW / 2, 96, fonte), row * 4 + margin}, 96 , 2 ,WHITE);

    // Botões para escolher a dificuldade
    if(botao((Rectangle){coluna * 2 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Facil", BLACK, BLUE, WHITE, fonte)){
        dificuldade = 1;
    }
    if(botao((Rectangle){coluna * 4 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Medio", BLACK, BLUE, WHITE, fonte)){
        dificuldade = 2;
    }
    if(botao((Rectangle){coluna * 6 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Dificil", BLACK, BLUE, WHITE, fonte)){
        dificuldade = 3;
    }

    // Para debug
    DrawTextEx(fonte, palavra, (Vector2){centro_x_texto(palavra, SW / 2, 96, fonte), row * 8 + margin}, 96 , 2 ,WHITE);

    // Chama a função para escolher a dificuldade e vai para o jogo
    if(dificuldade > 0){
        escolher_palavra_aleatoria(dificuldade);
        return FORCA;
    }

    return MENU;
}

// Escolhe uma palavra aleatória de um arquivo
void escolher_palavra_aleatoria(int dificuldade){
    
    // Abre o arquivo
    char caminho[100];
    sprintf(caminho, "lista_palavras/dificuldade_%d.txt", dificuldade);

    FILE *arquivo = fopen(caminho, "r");

    // Verifica por erros
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Conta quantas palavras há no arquivo
    int contador = 1;
    char buffer[1000];
    
    while(fgets(buffer, sizeof(buffer), arquivo) != NULL){
        contador++;
    }

    fclose(arquivo);

    // Abre o arquivo novamente
    arquivo = fopen(caminho, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo_2!\n");
        return;
    }

    // Escolhe uma palavra em aleatório
    int qual_palavra = rand() % contador;

    for(int i = 0; i < qual_palavra; i++){
        fgets(palavra, sizeof(palavra), arquivo);
    }

    // Remove o \n
    if(palavra[strlen(palavra) - 1] == '\n'){
        palavra[strlen(palavra) - 1] = '\0';
    }

    fclose(arquivo);
}

// Cria um botão e verifica se foi clicado
bool botao(Rectangle retangulo, float margin, char *texto, Color externo, Color interno, Color texto_cor, Font fonte){

    float diferenca;
    bool clicado = false;
    Vector2 mouse = GetMousePosition();

    // Verifica se o mouse está acima do botão
    if(CheckCollisionPointRec(mouse, retangulo)){

        diferenca = retangulo.height * sin(GetTime() * 2) * 0.1;

        retangulo.x -= diferenca / 2;
        retangulo.y -= diferenca / 2;
        retangulo.height += diferenca;
        retangulo.width += diferenca;

        // Verifica se o mouse clicou no notão
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            clicado = true;
        }

    }

    // Desenha o botão
    DrawRectangleRec(retangulo, externo);

    diferenca = retangulo.height * margin;

    retangulo.x += diferenca / 2;
    retangulo.y += diferenca / 2;
    retangulo.height -= diferenca;
    retangulo.width -= diferenca;

    DrawRectangleRec(retangulo, interno);

    diferenca = retangulo.height * margin;

    retangulo.x += diferenca / 2;
    retangulo.y += diferenca ;
    retangulo.height -= diferenca;
    retangulo.width -= diferenca;

    // Vefica se o texto não vai ficar maior que o botão
    Vector2 largura = MeasureTextEx(fonte, texto, retangulo.height, 2);
    while(largura.x > retangulo.width){
        retangulo.height--;
        retangulo.y += 0.5;
        largura = MeasureTextEx(fonte, texto, retangulo.height, 2);
    }

    // Desenha o texto
    DrawTextEx(fonte, texto, (Vector2){centro_x_texto(texto, retangulo.x + retangulo.width / 2, retangulo.height, fonte) , retangulo.y}, retangulo.height, 2, texto_cor);

    return clicado;
}

// Calcula o x em que o texto deve ser desenhado para ficar centralizado
float centro_x_texto(char *texto, int centro, int tamanho_fonte, Font fonte){

    Vector2 largura_texto = MeasureTextEx(fonte, texto, tamanho_fonte, 2);
    return centro - largura_texto.x / 2;

}