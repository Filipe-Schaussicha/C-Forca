#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "logica.h"

// Escolhe uma palavra aleatória de um arquivo
char *escolher_palavra_aleatoria(int dificuldade){
    
    // Abre o arquivo
    char caminho[100];
    sprintf(caminho, "lista_palavras/dificuldade_%d.txt", dificuldade);

    FILE *arquivo = fopen(caminho, "r");

    // Verifica por erros
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
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
        return NULL;
    }

    char *palavra_aleatoria = malloc(sizeof(char) * 100);

    // Escolhe uma palavra em aleatório
    int qual_palavra = rand() % contador;

    for(int i = 0; i < qual_palavra; i++){
        fgets(palavra_aleatoria, 100, arquivo);
    }

    // Remove o \n
    if(palavra_aleatoria[strlen(palavra_aleatoria) - 1] == '\n'){
        palavra_aleatoria[strlen(palavra_aleatoria) - 1] = '\0';
    }

    fclose(arquivo);

    return palavra_aleatoria;
}

void add_string(char *string, char c){

    int tamanho = strlen(string);

    string[tamanho] = c;
    string[tamanho + 1] = '\0';

}

bool letra_esta_string(char *string, char letra){

    int tamanho = strlen(string);

    for(int i = 0; i < tamanho; i++){

        if(string[i] == letra){
            return true;
        }

    }

    return false;
}

char *palavra_impressao(char *string, char *achadas, bool *tudo_achado){

    *tudo_achado = true;

    if(string == NULL){
        printf("Palavra Nula\n");
        return NULL;
    }

    int len = strlen(string);

    char *impressao = malloc(sizeof(char) * (len + 1));

    if(impressao == NULL){
        printf("Erro ao alocar palavra_impressao\n");
        return NULL;
    }

    impressao[0] = '\0';

    for(int i = 0; i < len; i++){

        if(letra_esta_string(achadas, string[i])){
            add_string(impressao, string[i]);
        }else{
            *tudo_achado = false;
            add_string(impressao, '_');
        }

    }

    return impressao;

}