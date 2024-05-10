/*Bibliotecas*/
# include <stdio.h> /*printf(), scanf()*/
# include <stdlib.h>
# include <string.h>
# include <locale.h> /*setlocale()*/
# include "console_v1.5.4.h"
# include "conio_v3.2.4.h"

/*gcc teste.c -o teste.exe -Wall -pedantic -Werror -Wextra console_v1.5.4.c conio_v3.2.4.c*/

/*Registro para os eventos do teclado*/
typedef struct _LE_TECLADO
{
    EVENTO tecla;
    int dados_Usuario;
}LE_TECLADO;

/*Registro para as escolhas do menu que o usuario irá fazer e as cores também*/
typedef struct _USUARIO
{
    int escolha_do_usuario;
    int controle_do_alt;
    int controla_evento;
    int enter_pressionado;
    int modo_teclas_especiais;
    int modo_leitura_dados;
}USUARIO;

int Le_Teclado(void);
    
int Le_Teclado() {
if (hit(KEYBOARD_HIT)) {
    EVENTO tecla = Evento();
    if (tecla.tipo_evento & KEY_EVENT) {
        if (tecla.teclado.status_tecla == LIBERADA) {
            switch (tecla.teclado.codigo_tecla) {
                case ESC:
                    exit(0);
                    break;
                /*Outros casos para tratamento de teclas*/
                case ENTER:
                    return 1;
                    break;
            }
        }
    }
}
    return 0;
}


int main(int argc, char *argv[]) {
    int numero;
    argc = argc;
    argv = argv;
    clrscr();
    do {
        if (kbhit()) { /*Verifica se uma tecla foi pressionada*/
            int tecla = getch(); /* Obtém a tecla pressionada*/
            if (tecla == 13) { /* 13 é o código ASCII para a tecla ENTER*/
                printf("Digite algo: ");
                scanf("%d", &numero);
                printf("Você digitou: %d\n", numero);
            }
            else if (tecla == 27) { /* 27 é o código ASCII para a tecla ESC*/
                exit(0);
            }
        }
    } while (1);

    return 0;
}




/*Referente a função Abre arquivo*/

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
            putchar(letra_arquivo);
            letra_arquivo = fgetc(arquivo_origem);
        }
        
    }
    else
    {
        puts("Abertura do arquivo deu errado!");
    }

    /*Fecha o arquivo*/
    fclose(arquivo_origem);

