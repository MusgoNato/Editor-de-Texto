/*Programa: Editor de Texto Simples.
Descrição: O programa será um editor de texto simples que possibilitará ao usuario abertura de arquivos,
troca de cores de fundo e texto, etc.
Programador: Hugo Josué Lema Das Neves
RGM: 47159 
Data da última modificação: 23/04/2024*/

/*Copiar e colar no prompt de comando
gcc principal.c -o editor.exe -Wall -pedantic -Werror -Wextra console_v1.5.4.c conio_v3.2.4.c funcoes.c*/

/*Bibliotecas*/
# include <stdio.h> /*printf(), scanf()*/
# include <stdlib.h>
# include <string.h>
# include <locale.h> /*setlocale()*/
# include "console_v1.5.4.h"
# include "conio_v3.2.4.h" /*clrscr*/
# include "funcoes.h" /*Abre_Arquivo(), TAM_NOME_ARQUIVO */

/*Programa principal*/
int main(int argc, char *argv[])
{
    /*Declarações*/
    STRINGS string;
    TAM_JANELA janela;
    COORD coordenadas_Janela;
    LE_TECLADO leitura;
    USUARIO op;

    /*Declaração das opções do menu*/
    char *opcoes[QTD_STRING] = {"ARQUIVO", "ALINHAMENTO", "ALTERAR X", "ALTERAR COR"};

    /*Declaração da opção do usuário*/
    op.escolha_do_usuario = 0;

    /*Definindo a altura e largura da janela*/
    janela.largura = 160;
    janela.altura = 40;

    /*Coordenadas da Janela, x e y, para eu poder imprimi-la na tela*/
    coordenadas_Janela.X = 1;
    coordenadas_Janela.Y = 1;


    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    /*Mudança para o idioma português*/
    setlocale(LC_ALL, "Portuguese");

    /*Limpa a tela*/
    clrscr();
    /*Loop infinito*/
    do
    {
      

        /*Chamada para desenhar minha janela para meu menu*/
        Desenha_Janela_Menu(&janela, coordenadas_Janela);
        
        /*Função que declara e colocar as opções do menu*/
        Imprime_op_Menu(&janela, coordenadas_Janela, &string, opcoes, &op);

        /*Função que faz a leitura das teclas do programa*/
        Le_Teclado(&leitura, &op);

        /*Chamada da função para realizar a abertura do arquivo
        Abre_Arquivo(&string);*/
        

    }while(1);
    
    


    /*Retorno para a main que encerrou com sucesso*/
    return 0;
}
