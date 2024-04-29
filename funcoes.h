/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define ALT_ESQUERDO 0x2
# define QTD_LETRAS 8
# define QTD_STRING 8
# define TAM_NOME_ARQUIVO 50
# define TAM_STRING 50

/*Estruturas*/

/*Registro que armazena o tamanho da minha janela com base na altura e largura*/
typedef struct _TAM_JANELA
{
    /*Largura e altura da janela*/
    int largura, altura;

}TAM_JANELA;

/*Registro para strings*/
typedef struct _STRINGS
{
    char arquivo_txt[TAM_NOME_ARQUIVO];
    char menu[QTD_STRING][TAM_STRING];
    char user_digitando[TAM_STRING];
    
}STRINGS;

/*Registro para os eventos do teclado*/
typedef struct _LE_TECLADO
{
    EVENTO tecla;
    char pega_evento;
}LE_TECLADO;

/*Registro para as escolhas do menu que o usuario irá fazer e as cores também*/
typedef struct _USUARIO
{
    int escolha_do_usuario;
    int controle_do_alt;
    int controla_evento;
    int enter_pressionado;
    COLORS cor_atalho;
}USUARIO;




/*Função que realiza a abertura do arquivo pedido ao usuário
Parametros: Uma string que conterá o nome do arquivo
Retorno: Nenhum*/
void Abre_Arquivo(STRINGS *);

/*Coloca minhas 'opções', na matriz de caracteres 'menu'*/
void Converte(STRINGS *, char **);

/*Função que realiza a cração da minha janela para o menu*/
void Desenha_Janela_Menu(TAM_JANELA *, COORD);

/*Função que imprime as opções de menu disponíveis*/
void Imprime_op_Menu(TAM_JANELA *, COORD, STRINGS *, USUARIO *, char *);

/*Vai ler as teclas do teclado e realizar as devidas chamadas para outras funções*/
void Le_Teclado(LE_TECLADO *, USUARIO *);

/*Função que mapeia as teclas de entrada para retornar para a verificação inicial da main*/
int Mapeia_teclas_Entrada(LE_TECLADO *);
