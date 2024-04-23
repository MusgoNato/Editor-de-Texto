/*Lógica dos protótipos criados no arquivo 'funcoes.h'*/

/*Bibliotecas/Constantes*/
# include <stdio.h> /*FILE, fopen(), printf(), */
# include "conio_v3.2.4.h"
# include "funcoes.h"

/*Função que abre o arquivo*/
void Abre_Arquivo(STRINGS *string)
{
    /*Cria uma variavel do tipo FILE que sera um ponteiro para o arquivo de origem*/
    FILE *arquivo_origem;
    char letra_arquivo;

    /*Insirir o arquivo desejado para abertura*/
    printf("\nInsira o arquivo que deseja abrir: ");
    scanf("%s", string->arquivo_txt);

    /*Verificação do arquivo para o modo leitura*/
    arquivo_origem = fopen(string->arquivo_txt, "r");

    /*Validação da abertura*/
    if(arquivo_origem != NULL)
    {
        letra_arquivo = fgetc(arquivo_origem);

        /*Loop até o fim do arquivo aberto*/
        while(letra_arquivo != EOF)
        {
            /*Pega cada letra do meu arquivo de origem para impressão na tela*/
            printf("%c", letra_arquivo);
            letra_arquivo = fgetc(arquivo_origem);
        }
        
    }
    else
    {
        printf("Abertura do arquivo deu errado!");
    }

    /*Fecha o arquivo*/
    fclose(arquivo_origem);
}

/*Desenha minha janela do menu*/
void Desenha_Janela_Menu(TAM_JANELA *janela)
{

    /*PRECISA DESENHAR AS BORDAS DA JANELA QUE VAI TER AS OPÇÕES DO MENU*/
    int i;
    gotoxy(1,1);

    /*Desenha a linha superior do menu*/
    for(i = 0; i < janela->largura; i++)
    {
        printf("=");
    }

    getch();
}