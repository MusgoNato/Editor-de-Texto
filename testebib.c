# include <stdio.h>
# include <stdlib.h>
# include "console_v1.5.5.h" 
# include <time.h>
# include <locale.h>

/*gcc testebib.c -o testebib.exe console_v1.5.5.c -Wall -pedantic -Wextra -Werror  */
/*
int retorno(EVENTO *e)
{
    if(e->teclado.status_teclas_controle & SHIFT_ESQUERDO_PRESSIONADO)
    {
        return 1;
    }
    return 0;
}

int retorno(EVENTO *);*/

int main(int argc, char*argv[])
{
    EVENTO e;
    char arquivo[30];
    int i = 0;
    int shift_pressed = 0;
    argc = argc;
    argv = argv;
    SystemParametersInfoA(SPI_SETKEYBOARDSPEED, 0, 0, 0);
    setlocale(LC_ALL, "Portuguese");
    do
    {
        if(hit(KEYBOARD_HIT))
        {
            e = Evento();
        if(e.tipo_evento & KEY_EVENT)
        {
            if(e.teclado.status_tecla == LIBERADA)
            {
                if(e.teclado.key_code == ESC)
                {
                    break;
                }
                if(e.teclado.key_code == ENTER)
                {
                    arquivo[i] = '\0';
                    break;
                }

                /*Foi pressionado o shift*/
                if(shift_pressed)
                {
                    /*Verifca se liberou o shift*/
                    if(e.teclado.status_tecla == LIBERADA)
                    {
                        arquivo[i] = e.teclado.ascii_code;
                        
                        shift_pressed = 0;
                    }
    
                    
                }
                else
                {
                    
                    if(e.teclado.key_code >= 33 && e.teclado.key_code <= 254)
                    {
                        arquivo[i] = e.teclado.ascii_code;
                        
                    }
                    
                }
                
            }
            else
            {
                if(e.teclado.status_teclas_controle & SHIFT_ESQUERDO_PRESSIONADO)
                {
                    shift_pressed = 1;
                }
                
            }
        }
        }
        
    
        	
    }
    while(1);
    printf("%s", arquivo);

    return 0;

}