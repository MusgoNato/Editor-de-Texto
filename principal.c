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
    /*Declarações das estruturas*/
    STRINGS string;
    TAM_JANELA janela;
    COORD coordenadas_Janela;
    LE_TECLADO leitura;
    USUARIO op;

    /*Declaração das opções do menu*/
    char *opcoes[QTD_STRING] = {"ARQUIVO", "ALINHAMENTO", "ALTERAR X", "COR FUNDO", "COR TEXTO", };

    /*Declaração dos atalhos*/
    char letras[QTD_LETRAS] = {'A', 'L', 'X', 'F', 'T'};

    op.enter_pressionado = -1;

    /*Declaração da opção do usuário*/
    op.escolha_do_usuario = 0;

    /*Controle do alt*/
    op.controle_do_alt = 0;

    /*Controla o desenho da janela, para que eu consiga mover o cursor,
    é inicializado com 1 pois preciso que imprima na tela pela 1° vez a janela*/
    op.controla_evento = 1;

    op.modo_leitura_dados = 0;

    op.modo_teclas_especiais = 1;

    op.esc_apertado = 1;

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
    setlocale(LC_ALL, " ");

    /*Limpa a tela*/
    clrscr();

    /*Coloca a 'opções' em uma matriz de caractere 'menu' para ser usada em outra função adiante*/
    Converte(&string, opcoes);
    
    /*Chamada para desenhar minha janela para meu menu*/
    Desenha_Janela_Menu(&janela, coordenadas_Janela);

    /*Loop infinito*/
    while(op.esc_apertado)
    {  
        if(op.controla_evento)
        {   
            
            /*Função que declara e colocar as opções do menu*/
            Imprime_op_Menu(&janela, coordenadas_Janela, &string, &op, letras);
            op.controla_evento = 0;
        }
        
        /*Função que faz a leitura das teclas do programa*/
        Le_Teclado(&leitura, &op);

    }  

    /*Retorno para a main que encerrou com sucesso*/
    return 0;
}
