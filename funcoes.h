/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define ALT_ESQUERDO 0x2
# define QTD_LETRAS 5
# define QTD_STRING 5
# define TAM_NOME_ARQUIVO 50
# define TAM_STRING 50
# define ESPACAMENTO 10

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
    char submenu_arquivo[1];
    
}STRINGS;

/*Registro para os eventos do teclado*/
typedef struct _LE_TECLADO
{
    EVENTO tecla;
    
}LE_TECLADO;

/*Registro para as escolhas do menu que o usuario irá fazer e as cores também*/
typedef struct _USUARIO
{
    int escolha_do_usuario;
    int controle_do_alt;
    int esc_apertado;
    int controla_evento;
    int enter_pressionado;
    int modo_teclas_especiais;
    int modo_leitura_dados;
    int numero_convertido;
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

/*Pede o caractere para o TAB*/
void Caractere_X(LE_TECLADO *leitura, USUARIO *op);

/*Mostra o submenu arquivo para o usuario escolher*/
void Submenu_Arquivo();

/*Faz os submenus
void Submenu_Arquivo(COORD, USUARIO *);*/


