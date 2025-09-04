// Telas do jogo
typedef enum telas {
    MENU, 
    FORCA,
    TECLADO,
    FIM_JOGO
}telas;

#define SW 1366
#define SH 768

Font carrega_fonte(char *caminho, int tamanho);

int menu(Font fonte, char* palavra);

bool botao(Rectangle retangulo, float margin, char *texto, Color externo, Color interno, Color texto_cor, Font fonte);

float centro_x_texto(char *texto, int centro, int tamanho_fonte, Font fonte);