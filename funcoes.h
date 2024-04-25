/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define TAM_NOME_ARQUIVO 50
# define TAM_STRING 50
# define QTD_STRING 4

/*Estruturas*/

/*Registro que armazena o tamanho da minha janela com base na altura e largura*/
typedef struct _TAM_JANELA
{
    /*Largura e altura da janela*/
    int largura, altura;

    /*Coordenadas para controlar o desenho da janela
    int x_Janela, y_Janela;*/

}TAM_JANELA;

/*Registro para strings*/
typedef struct _STRINGS
{
    char arquivo_txt[TAM_NOME_ARQUIVO];
    char menu[QTD_STRING][TAM_STRING];
    
}STRINGS;

/*Registro para os eventos do teclado*/
typedef struct _LE_TECLADO{
    EVENTO tecla;
}LE_TECLADO;

/*Registro para as escolhas do menu que o usuario irá fazer*/
typedef struct _USUARIO{
    int escolha_do_usuario;
}USUARIO;



/*Função que realiza a abertura do arquivo pedido ao usuário
Parametros: Uma string que conterá o nome do arquivo
Retorno: Nenhum*/
void Abre_Arquivo(STRINGS *);

/*Função que realiza a cração da minha janela para o menu*/
void Desenha_Janela_Menu(TAM_JANELA *, COORD);

/*Função que imprime as opções de menu disponíveis*/
void Imprime_op_Menu(TAM_JANELA *, COORD, STRINGS *, char **, USUARIO *);

/*Vai ler as teclas do teclado e realizar as devidas chamadas para outras funções*/
void Le_Teclado(LE_TECLADO *, USUARIO *);