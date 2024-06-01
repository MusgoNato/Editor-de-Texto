/*Programa: Editor de Texto Simples.
Descrição: Programa que será capaz de editar, inserir e sobrescrever caracteres, podendo o usuario trocar de cor, tanto de
texto como do fundo do prompt. Pode abrir arquivos de qualquer tamanho e modifica-los.
Programador: Hugo Josué Lema Das Neves
RGM: 47159 
Data da última modificação: 19/05/2024*/

/*Copiar e colar no prompt de comando
    */

/*Executavel gerado após a linha de compilação acima
editor.exe*/

/*Bibliotecas*/
# include <locale.h> /*setlocale()*/
# include "console_v1.5.5.h" /*setDimensaoJanela()*/
# include "conio_v3.2.4.h" /*clrscr(), textcolor(), textbackground(), */
# include "funcoes.h" /*Abre_Arquivo(), Copiar_caracteres_pra_matrizes(), Desenha_Janela_Menu(), Imprime_op_Menu(), Inicializacao_Variaveis(),
Le_Teclado(), QTD_STRING, QTD_LETRAS,*/

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

    /*Mudança para o idioma nativo do Sistema operacional, devido a compatibilidade, manteve-se " " pois pode mudar de sistema para sistema,
    o "Portuguese" pode ser "PT-BR", etc*/
    setlocale(LC_ALL, " ");

    /*Inicializa variaveis*/
    Inicializacao_Variaveis(&string, &op, &janela);

    /*Seta a Dimesao da minha janela*/
    setDimensaoJanela(string.limite_maximo_Janela.X, string.limite_maximo_Janela.Y);

    /*Silenciar warnings*/
    argc = argc;
    argv = argv;


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
            
            /*Reseta a variavel para controlar as cores da janela*/
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
