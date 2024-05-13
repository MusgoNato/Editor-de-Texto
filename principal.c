/*Programa: Editor de Texto Simples.
Descrição: O programa será um editor de texto simples que possibilitará ao usuario abertura de arquivos,
troca de cores de fundo e texto, etc.
Programador: Hugo Josué Lema Das Neves
RGM: 47159 
Data da última modificação: 23/04/2024*/

/*Copiar e colar no prompt de comando
gcc principal.c -o editor.exe -Wall -pedantic -Werror -Wextra console_v1.5.5.c conio_v3.2.4.c funcoes.c*/

/*Bibliotecas*/
# include <stdio.h> /*printf(), scanf()*/
# include <stdlib.h>
# include <string.h>
# include <locale.h> /*setlocale()*/
# include "console_v1.5.5.h"
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

    /*Declaração da opção do usuário*/
    op.escolha_do_usuario = 0;

    /*Controle do alt*/
    op.controle_do_alt = 0;

    /*Controla o desenho da janela, para que eu consiga mover o cursor,
    é inicializado com 1 pois preciso que imprima na tela pela 1° vez a janela*/
    op.controla_evento = 1;

    /*Variavel para saida do loop principal da main*/
    op.esc_apertado = 1;

    /*Precisa imprimir ao menos 1 vez*/
    op.imprime_janela_cor_diferente = 1;

    /*Coordenadas da Janela, x e y, para eu poder imprimi-la na tela*/
    janela.coordenadas_janela.X = 1;
    janela.coordenadas_janela.Y = 1;

    /*Inicialização da quantidade de linhas no arquivo*/
    string.index_linha_matriz = 0;


    /*Silenciar warnings*/
    argc = argc;
    argv = argv;

    /*Mudança para o idioma nativo do Sistema operacional, devido a compatibilidade, manteve-se " " pois pode mudar de sistema para sistema,
    o "Portuguese" pode ser "PT-BR", etc*/
    setlocale(LC_ALL, " ");

    /*Limpa a tela*/
    clrscr();

    /*Coloca a 'opções' em uma matriz de caractere 'menu' para ser usada em outra função adiante*/
    Copiar_caracteres_pra_matrizes(&string, opcoes, submenu_op_arquivo, submenu_op_cor);

    /*A cor de fundo ja começa com preto por definição e a cor de texto padrão para os caracteres*/
    string.cores_texto = LIGHTGRAY;
    string.cores_background = BLACK;
        
    /*Loop infinito*/
    while(op.esc_apertado)
    {
        /*Imprime as janelas e as cores de fundo e de texto respectiva a qual foi escolhida*/
        if(op.imprime_janela_cor_diferente)
        {
            /*Trocar a cor do fundo*/
            textbackground(string.cores_background);

            /*Trocar a cor do texto*/            
            textcolor(string.cores_texto);

            /*Chamada para desenhar minha janela para meu menu principal*/
            Desenha_Janela_Menu(&janela);
            
            op.imprime_janela_cor_diferente = 0;
        }

        /*Caso a janela tenha que ser impressa ou tenha uma mudança de cor*/
        if(op.controla_evento || op.imprime_janela_cor_diferente)
        {   
            /*Função que declara e colocar as opções do menu*/
            Imprime_op_Menu(&janela, &string, &op, letras);

            /*Reseta a variavel a 0 para controle do menu principal*/
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
