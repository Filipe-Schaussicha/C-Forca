#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "logica.h"
#include "visual.h"

#define COR_BORDA_BOTAO BLACK
#define COR_BOTAO   BLUE
#define COR_TEXTO_BOTAO WHITE

int jogo(char *string, Font fonte, Texture2D forca){

    // Variáveis de referência para ajudar no possicionamento
    float coluna = SW * 0.1;
    float row = SH * 0.1;

    // Desenha a forca
    DrawTextureEx(forca, (Vector2){coluna * 1.25 , row * 3}, 0.0, 0.65,  WHITE);

    int erros = 0;

    static char tentativas[100] = "\n -AEIOU";

    // Deixa as palavras desconhecidas como _ e mostra as achadas
    char *impressao = palavra_impressao(string, tentativas);

    if(string == NULL || impressao == NULL){
        return MENU;
    }

    // Quebra palavras grandes em duas linhas
    if((int)MeasureTextEx(fonte, impressao, 100, 15).x > coluna * 5 && letra_esta_string(impressao, ' ')){

        int len = strlen(impressao);

        for(int i = 0; i < len; i++){
            if(impressao[i] == ' '){
                impressao[i] = '\n';
                break;
            }
        }
    }

    //printf("%s\n", impressao); 

    // Desenha a palavra
    DrawTextEx(fonte, impressao, (Vector2){coluna * 3, row * 6.75}, 100, 15, WHITE);

    // Desenha as tentativas anteriores
    DrawTextEx(fonte, &tentativas[3], (Vector2){coluna * 3.5, row * 3}, 65, 20, YELLOW);

    free(impressao);

    //if(botao()){
    //    return TECLADO;
    //}

    return FORCA;
}


Font carrega_fonte(char *caminho, int tamanho){

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

    return LoadFontEx(caminho, tamanho, chars, charCount);
}


int menu(Font fonte, char **string){

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
    if(botao((Rectangle){coluna * 2 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Facil", COR_BORDA_BOTAO, COR_BOTAO, COR_TEXTO_BOTAO, fonte)){
        dificuldade = 1;
    }
    if(botao((Rectangle){coluna * 4 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Medio", COR_BORDA_BOTAO, COR_BOTAO, COR_TEXTO_BOTAO, fonte)){
        dificuldade = 2;
    }
    if(botao((Rectangle){coluna * 6 + margin, row * 6 + margin, coluna * 2 - margin * 2, row * 2 - margin * 2}, 0.1, "Dificil", COR_BORDA_BOTAO, COR_BOTAO, COR_TEXTO_BOTAO, fonte)){
        dificuldade = 3;
    }

    // Chama a função para escolher a dificuldade e vai para o jogo
    if(dificuldade > 0){
        
        *string = escolher_palavra_aleatoria(dificuldade);

        if(*string != NULL){
            printf("%s\n", *string);
            return FORCA;
        }
    }

    return MENU;
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