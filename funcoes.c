/*Lógica dos protótipos criados no arquivo 'funcoes.h'*/

/*Bibliotecas/Constantes*/
# include <stdio.h> /*FILE, fopen(), printf(), */
# include "console_v1.5.4.h"
# include "conio_v3.2.4.h" /*gotoxy()*/
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
void Desenha_Janela_Menu(TAM_JANELA *janela, COORD coordenadas_Janela)
{
    /*PRECISA DESENHAR AS BORDAS DA JANELA QUE VAI TER AS OPÇÕES DO MENU*/
    int i;

    /*Desenha a linha superior do menu*/
    for(i = 0; i < janela->largura; i++)
    {
        gotoxy(coordenadas_Janela.X + i, coordenadas_Janela.Y);
        printf("=");
    }

    /*Coluna esquerda*/
    for(i = 0; i < janela->altura; i++)
    {
        gotoxy(coordenadas_Janela.X, coordenadas_Janela.Y + i);
        printf("|");
    }

    /*Linha inferior*/
    for(i = 0; i < janela->largura; i++)
    {
        /*Necessário o incremento do i em 1, para nao borrar o '|' da coluna esquerda,
        há de se decrementar a janela->altura pois o printf da um quebra linha, para isso imprimir o caractere '=' uma linha depois, se decrementa o y*/
        gotoxy(coordenadas_Janela.X + i + 1, coordenadas_Janela.Y + janela->altura - 1);
        printf("=");
    }

    /*Coluna Direita*/
    for(i = 0; i < janela->altura; i++)
    {
        /*X recebe o valor da largura, assim eu tenho a coordenada do fim da linha superior, feito isso, somente incrementar o y até a altura
        definida*/
        gotoxy(coordenadas_Janela.X + janela->largura, coordenadas_Janela.Y + i);
        printf("|");
    }

    /*Linha inferior a linha superior*/
    /*A largura é decrementada pois passa do limite da coluna direita*/
    for(i = 0; i < janela->largura - 1; i++)
    {
        /*Dividindo a largura e altura e, somando com a coordenadas_Janela.Y, tenho o lugar para imprimir a linha inferior a superior,
        somente é necessário incrementar o x, x + 1 pois ele 'come' a coluna da esquerda, para ajustar incrementei em +1 e decrementei a largura na condição de parada*/
        gotoxy(coordenadas_Janela.X + i + 1, coordenadas_Janela.Y + janela->largura/janela->altura);

        /*LEMBRA-SE:
        TENHO O LUGAR PARA PEDIR AO USUARIO JÁ, SOMENTE PEGAR A MESMA IDEIA DO GOTOXY ACIMA, POIS JA TENHO A LINHA REFERENTE AO INFERIOR DAS OPÇÕES NO MENU*/
        printf("=");
    }
    
}


/*Função que imprime as opções de menu na tela*/
void Imprime_op_Menu(TAM_JANELA *janela, COORD coordenadas_Janela, STRINGS *string, char **opcoes)
{
    int i;
    int tam_opcao_menu = 0;

    /*Espaçamento fixo entre as opções*/
    int espacamento = 10;

    /*Declaração por meio do snprintf, no 'opcoes' contem as opcoes definidas no inicio do programa, o menu, uma matriz de strings,
    contera todas as opções disponiveis, pois é feita a atribuição de opcoes a menu*/
    for(i = 0; i < QTD_STRING; i++)
    {
        snprintf(string->menu[i], TAM_STRING, "%s", opcoes[i]);
    }

    /*Lugar de escrita das opções do menu*/
    gotoxy(coordenadas_Janela.X + 1, coordenadas_Janela.Y + janela->largura/janela->altura/2);
    for(i = 0; i < QTD_STRING; i++)
    {   
        /*Seta o lugar aonde deve ser impresso*/
        gotoxy(coordenadas_Janela.X + tam_opcao_menu + 1, coordenadas_Janela.Y + janela->largura/janela->altura/2);
        
        /*Imprime o menu por cada opção*/
        printf("%s", string->menu[i]);
        
        /*O tamanho da opcao armazena o tamanho da string do menu e o soma com a quantidade de espaçamento declarado fixo, isso faz com que haja um espaçamento
        independente do tamanho da string */
        tam_opcao_menu += strlen(string->menu[i]) + espacamento;
    }

}

/*Função que le o teclado do usuario*/
void Le_Teclado(LE_TECLADO *leitura)
{

    /*Verificação para um 'hit' do teclado*/
    if(hit(KEYBOARD_HIT))
    {
        /*Atribuição do evento que ocorreu*/
        leitura->tecla = Evento();

        /*Verificação caso seja um evento originário do teclado*/
        if(leitura->tecla.tipo_evento & KEY_EVENT)
        {
            /*Verificação da tecla se foi liberada ao pressionada*/
            if(leitura->tecla.teclado.status_tecla == LIBERADA)
            {
                /*Casos para o menu*/
                switch(leitura->tecla.teclado.codigo_tecla)
                {

                    /*É necessaria primeiro a navegação do menu por meio das teclas, depois eu vejo o enter*/
                    case SETA_PARA_BAIXO:
                    {
                        printf("baixo");
                        break;
                    }
                    case SETA_PARA_CIMA:
                    {
                        printf("cima");
                        break;
                    }
                    case SETA_PARA_DIREITA:
                    {
                        printf("direita");
                      
                        break;
                    }
                    case SETA_PARA_ESQUERDA:
                    {
                        printf("esquerda");
                        
                        break;
                    }
                    default:
                    {
                        exit(0);
                    }
                }
            }
            
        }
    }
}