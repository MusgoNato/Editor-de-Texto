/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define ALT_ESQUERDO 0x2
# define QTD_LETRAS 5
# define QTD_STRING 5
# define TAM_NOME_ARQUIVO 50
# define TAM_STRING 50
# define ESPACAMENTO 10
# define BLOCO_DE_IMPRESSAO 40
# define TAM_BUFFER 1024

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
    FILE *arquivo_origem;
    char menu[QTD_STRING][TAM_STRING];
    char **matriz_de_linhas;
    char submenu_arquivo[2][TAM_STRING];
    char submenu_cores[16][TAM_STRING];
    int caracteres_no_arquivo;
    int modo_insercao;
    int controla_sub;
    int index_linha_matriz;
    int tamanho_das_linhas[LARGURA];
    int modo;
    int controla_impressao_arquivo;
    int tecla_pgd;
    int limite_impressao_arq;

    /*Essa matriz vai guardar o save da tela, pra depois somente recolocar, após o usuario ter pressionado qualquer submenu*/
    char *Tela;

    COORD vetor_cord_menu[QTD_STRING];
    COORD limite_maximo_Janela;
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
    int numero_TAB_X;
    int imprime_janela_cor_diferente;
    COLORS cor_atalho;
    COORD coordenadas_submenus;
}USUARIO;


/*Função que realiza a abertura do arquivo pedido ao usuário
Parametros: Ponteiro para estrutura STRINGS
Retorno: 
Nenhum*/
void Abre_Arquivo(STRINGS *);

/*Pede o caractere para o TAB
Parametros :
1° -> Ponteiro para LE_TECLADO
2° -> Ponteiro para USUARIO 
Retorno : 
Nenhum*/
void Caractere_X(LE_TECLADO *, USUARIO *, STRINGS *);

/*Coloca minhas 'opções', na matriz de caracteres 'menu'
Parametros :
1° -> Ponteiro para estrutura STRINGS
2° -> Variavel tipo char ponteiro para ponteiro
3° -> Variavel tipo char ponteiro para ponteiro
4° -> Variavel tipo char ponteiro para ponteiro
Retorno : 
Nenhum
*/
void Copiar_caracteres_pra_matrizes(STRINGS *, char **, char **, char **);

/*Função que realiza a cração da minha janela para o menu
Parametros :
1° -> Ponteiro para estrutura TAM_JANELA (Contera as variaveis necessarias para impressão da janela na tela)
Retorno : 
Nenhum
*/
void Desenha_Janela_Menu(TAM_JANELA *);

/*Função que escreve caracteres do usuario no arquivo
Parametros :
1° -> Ponteiro para estrutura STRINGS
Retorno : 
Nenhum*/
void Escreve_no_Arquivo(STRINGS *);

/*Responsável por imprimir o arquivo escolhido
Parametros : 
1° -> Ponteiro para estrutura STRINGS
Retorno : 
Nenhum*/
void Imprimir_Arquivo(STRINGS *);

/*Função que imprime as opções de menu disponíveis
Parametros :
1° -> Ponteiro para estrutura TAM_JANELA
2° -> Ponteiro para estrutura STRINGS
3° -> Ponteiro para estrutura USUARIO
4° -> Ponteiro do tipo char
Retorno :
Nenhum
*/
void Imprime_op_Menu(TAM_JANELA *, STRINGS *, USUARIO *, char *);

/*Inicializa as variaveis do programa
Paremetros :
1° -> Ponteiro para estrutura STRINGS
2° -> Ponteiro para estrutura USUARIO
3° -> Ponteiro para estrutura TAM_JANELA
Retorno : 
Nenhum
*/

void Inicializacao_Variaveis(STRINGS *, USUARIO *, TAM_JANELA *);

/*Vai ler as teclas do teclado e realizar as devidas chamadas para outras funções
Parametros :
1° -> Ponteiro para estrutura LE_TECLADO
2° -> Ponteiro para estrutura USUARIO
3° -> Ponteiro para estrutura STRINGS
Retorno :
Nenhum
*/
void Le_Teclado(LE_TECLADO *, USUARIO *, STRINGS *);

/*Função que mapeia as teclas de entrada para retornar para a verificação inicial da main
Parametros : 
1° -> Ponteiro para estrutura LE_TECLADO
Retorno :
Variavel do tipo inteiro, ela contera 1 caso a tecla que esta sendo verificada dentro da função for pressionada,
caso contrário retorna 0.
*/
int Mapeia_teclas_Entrada(LE_TECLADO *);

/*Função responsável por salvar o arquivo aberto
Parametros :
1° -> Ponteiro para STRINGS
Retorno : 
Nenhum*/
void Salvar_Arquivo(STRINGS *);

/*Função responsável por contar quantos caracteres existem dentro do meu arquivo já aberto, o retorno da função servirá para alocar memoria na matriz de strings
Parametros :
1° -> Ponteiro para arquivo do tipo FILE
Retorno :
Retorna uma variavel do tipo 'int' com a quantidade de caracteres presentes dentro do arquivo que foi passado commo parametro*/
int Pega_caracteres_do_arquivo(FILE *);

/*Mostra o submenu arquivo para o usuario escolher
Parametros :
1° -> Ponteiro para estrutura STRINGS
2° -> Ponteiro para estrutura USUARIO
Retorno :
Nenhum*/
void Submenu_Arquivo(STRINGS *);

/*Função que imprime as subopções da opção 'COR FUNDO' no menu principal
Paramentros : 
1° -> Ponteiro para estrutura STRINGS
2° -> Ponteiro para estrutura USUARIO
Retorno : 
Nenhum*/
void Submenu_background(STRINGS *, USUARIO *);

/*Função que muda a cor de texto
Paramentros : 
1° -> Ponteiro para estrutura STRINGS
2° -> Ponteiro para estrutura USUARIO
Retorno : 
Nenhum*/
void Submenu_cor_texto(STRINGS *, USUARIO *);