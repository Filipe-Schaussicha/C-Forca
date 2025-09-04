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
        fgets(palavra_aleatoria, sizeof(palavra_aleatoria), arquivo);
    }

    // Remove o \n
    if(palavra_aleatoria[strlen(palavra_aleatoria) - 1] == '\n'){
        palavra_aleatoria[strlen(palavra_aleatoria) - 1] = '\0';
    }

    fclose(arquivo);

    return palavra_aleatoria;
}

