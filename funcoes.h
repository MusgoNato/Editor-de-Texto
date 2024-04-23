/*Protótipos de funções de declarações de registros (structs)*/

/*Definições de constantes*/
# define TAM_NOME_ARQUIVO 50

/*Estruturas*/

/*Registro que armazena o tamanho da minha janela com base na altura e largura*/
typedef struct _TAM_JANELA
{
    int largura;
    int altura;

}TAM_JANELA;

/*Registro para strings*/
typedef struct _STRINGS
{
    char arquivo_txt[TAM_NOME_ARQUIVO];
}STRINGS;




/*Função que realiza a abertura do arquivo pedido ao usuário
    Parametros: Uma string que conterá o nome do arquivo
    Retorno: Nenhum*/
void Abre_Arquivo(STRINGS *);

/*Função que realiza a cração da minha janela para o menu*/
void Desenha_Janela_Menu(TAM_JANELA *);