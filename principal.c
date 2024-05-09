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
    LE_TECLADO leitura;
    USUARIO op;

    /*Declaração das opções do menu*/
    char *opcoes[QTD_STRING] = {"ARQUIVO", "ALINHAMENTO", "ALTERAR X", "COR FUNDO", "COR TEXTO"};

    /*Declaração dos atalhos*/
    char letras[QTD_LETRAS] = {'A', 'L', 'X', 'F', 'T'};

    /*Declaração das opções do submenu arquivo*/
    char *submenu_op_arquivo[2] = {"ABRIR", "SALVAR"};

    /*Declaração das opções do submenu troca cores do texto*/
    char *submenu_op_cor[16] = {"BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE"};

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
    janela.coordenadas_janela.X = 1;
    janela.coordenadas_janela.Y = 1;

    /*A cor de fundo ja começa com preto por definição e a cor de texto padrão para os caracteres*/
    string.cores_background = BLACK;
    string.cores_texto = LIGHTGRAY;

    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    /*Mudança para o idioma português*/
    setlocale(LC_ALL, " ");

    /*Limpa a tela*/
    clrscr();

    /*Coloca a 'opções' em uma matriz de caractere 'menu' para ser usada em outra função adiante*/
    Copiar_caracteres_pra_matrizes(&string, opcoes, submenu_op_arquivo, submenu_op_cor);
    
    /*Chamada para desenhar minha janela para meu menu*/
    Desenha_Janela_Menu(&janela);

    /*Loop infinito*/
    while(op.esc_apertado)
    {  
        if(op.controla_evento)
        {   
            /*Trocar a cor do fundo*/
            textbackground(string.cores_background);

            /*Trocar a cor do texto*/            
            textcolor(string.cores_texto);

            /*Função que declara e colocar as opções do menu*/
            Imprime_op_Menu(&janela, &string, &op, letras);

            op.controla_evento = 0;
        }
        
        /*Função que faz a leitura das teclas do programa*/
        Le_Teclado(&leitura, &op, &string);

    }  

    /*Devolve as cores de fundo e de texto para as originais*/
    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    /*Retorno para a main que encerrou com sucesso*/
    return 0;
}
