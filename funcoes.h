/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define ALT_ESQUERDO 0x2
# define QTD_LETRAS 5
# define QTD_STRING 5
# define TAM_NOME_ARQUIVO 50
# define TAM_STRING 50
# define ESPACAMENTO 10

/*Tamanho da minha janela*/
# define LARGURA 160
# define ALTURA 40

/*Estruturas*/

/*Registro que armazena a coordenada da minha janela*/
typedef struct _TAM_JANELA
{
    /*Coordenadas da janela*/
    COORD coordenadas_janela;

}TAM_JANELA;

/*Registro para strings*/
typedef struct _STRINGS
{
    char arquivo_txt[TAM_NOME_ARQUIVO];
    char menu[QTD_STRING][TAM_STRING];
    char matriz_de_linhas[ALTURA][LARGURA];
    char submenu_arquivo[2][TAM_STRING];
    char submenu_cores[16][TAM_STRING];
    int modo_insercao;
    int controla_sub;
    int index_linha_matriz;
    int tamanho_das_linhas[LARGURA];
    COORD posicao_cursor_escrita;
    COLORS cores_background;
    COLORS cores_texto;
}STRINGS;

/*Registro para os eventos do teclado*/
typedef struct _LE_TECLADO
{
    EVENTO tecla;
    
}LE_TECLADO;

/*Registro para as escolhas do menu que o usuario irá fazer e as cores do atalho também*/
typedef struct _USUARIO
{
    int escolha_do_usuario;
    int controle_do_alt;
    int esc_apertado;
    int controla_evento;
    int enter_pressionado;
    int numero_convertido;
    int imprime_janela_cor_diferente;
    COLORS cor_atalho;
    COORD coordenadas_submenus;
}USUARIO;





/*Função que realiza a abertura do arquivo pedido ao usuário
Parametros: Uma string que conterá o nome do arquivo
Retorno: Nenhum*/
void Abre_Arquivo(STRINGS *);

/*Coloca minhas 'opções', na matriz de caracteres 'menu'*/
void Copiar_caracteres_pra_matrizes(STRINGS *, char **, char **, char **);

/*Função que realiza a cração da minha janela para o menu*/
void Desenha_Janela_Menu(TAM_JANELA *);

/*Função que imprime as opções de menu disponíveis*/
void Imprime_op_Menu(TAM_JANELA *, STRINGS *, USUARIO *, char *);

/*Vai ler as teclas do teclado e realizar as devidas chamadas para outras funções*/
void Le_Teclado(LE_TECLADO *, USUARIO *, STRINGS *);

/*Função que mapeia as teclas de entrada para retornar para a verificação inicial da main*/
int Mapeia_teclas_Entrada(LE_TECLADO *);

/*Pede o caractere para o TAB*/
void Caractere_X(LE_TECLADO *, USUARIO *);

/*Mostra o submenu arquivo para o usuario escolher*/
void Submenu_Arquivo(STRINGS *, USUARIO *);

/*Função que imprime as subopções da opção 'COR FUNDO' no menu principal*/
void Submenu_background(STRINGS *, USUARIO *);

/*Função que muda a cor de texto*/
void Submenu_cor_texto(STRINGS *, USUARIO *);

/*Função que escreve caracteres do usuario no arquivo*/
void Escreve_no_Arquivo(STRINGS *);


