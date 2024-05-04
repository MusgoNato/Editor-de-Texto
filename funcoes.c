/*Lógica dos protótipos criados no arquivo 'funcoes.h'*/

/*Bibliotecas/Constantes*/
# include <stdio.h> /*FILE, fopen(), printf(), */
# include <string.h> /*strlen(), strchr()*/
# include <ctype.h>
# include "console_v1.5.4.h" /*SETAS_DE_DIREÇÃO*/
# include "conio_v3.2.4.h" /*gotoxy()*/
# include "funcoes.h"

/*Função que abre o arquivo*/
void Abre_Arquivo(STRINGS *string)
{
    /*Cria uma variavel do tipo FILE que sera um ponteiro para o arquivo de origem*/
    FILE *arquivo_origem;
    char letra_arquivo;

    /*Insirir o arquivo desejado para abertura*/
    puts("\nInsira o arquivo que deseja abrir: ");
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
}

/*Converete a string nas suas devidas posições*/
void Converte(STRINGS *string, char **opcoes, char **submenu)
{
    int i;
    /*Declaração por meio do snprintf, no 'opcoes' contem as opcoes definidas no inicio do programa, o menu, uma matriz de strings,
    contera todas as opções disponiveis, pois é feita a atribuição de 'opcoes' a 'menu'*/
    for(i = 0; i < QTD_STRING; i++)
    {
        snprintf(string->menu[i], TAM_STRING, "%s", opcoes[i]);
    }

    /*Conversão para o submenu arquivo de acordo com o seu tamanho*/
    for(i = 0; i <= 1; i++)
    {
        snprintf(string->submenu_arquivo[i], TAM_STRING, "%s", submenu[i]);
    }
}

/*Desenha minha janela do menu*/
void Desenha_Janela_Menu(TAM_JANELA *janela, COORD coordenadas_Janela)
{
    int i;

    /*Desenha a linha superior do menu*/
    for(i = 0; i < janela->largura; i++)
    {
        gotoxy(coordenadas_Janela.X + i, coordenadas_Janela.Y);
        putchar('=');
    }

    /*Coluna esquerda*/
    for(i = 0; i < janela->altura; i++)
    {
        gotoxy(coordenadas_Janela.X, coordenadas_Janela.Y + i);
        putchar('|');
    }

    /*Linha inferior*/
    for(i = 0; i < janela->largura; i++)
    {
        /*Necessário o incremento do i em 1, para nao borrar o '|' da coluna esquerda,
        há de se decrementar a janela->altura pois o printf da um quebra linha, para isso imprimir o caractere '=' uma linha depois, se decrementa o y*/
        gotoxy(coordenadas_Janela.X + i + 1, coordenadas_Janela.Y + janela->altura - 1);
        putchar('=');
    }

    /*Coluna Direita*/
    for(i = 0; i < janela->altura; i++)
    {
        /*X recebe o valor da largura, assim eu tenho a coordenada do fim da linha superior, feito isso, somente incrementar o y até a altura
        definida*/
        gotoxy(coordenadas_Janela.X + janela->largura, coordenadas_Janela.Y + i);
        putchar('|');
    }

    /*Linha inferior a linha superior*/
    /*A largura é decrementada pois passa do limite da coluna direita*/
    for(i = 0; i < janela->largura - 1; i++)
    {
        /*Dividindo a largura e altura e, somando com a coordenadas_Janela.Y, tenho o lugar para imprimir a linha inferior a superior,
        somente é necessário incrementar o x, x + 1 pois ele 'come' a coluna da esquerda, para ajustar incrementei em +1 e decrementei a largura na condição de parada*/
        gotoxy(coordenadas_Janela.X + i + 1, coordenadas_Janela.Y + janela->largura/janela->altura);
        putchar('=');
    }
    
}



/*Função que imprime as opções de menu na tela*/
void Imprime_op_Menu(TAM_JANELA *janela, COORD coordenadas_Janela, STRINGS *string, USUARIO *op, char *letras)
{
    int i;

    /*Armazenará o tamanho de cada string*/
    int tam_opcao_menu = 0;

    /*Armazenará a posição da letra de atalho encontrada nas opções de menu*/
    int pos;

    /*Armazenará um ponteiro para a posição da letra encontrada nas strings*/
    char *p_posicao_letra;

    /*Armazenará a coordenada de onde devo destacar a tecla de atalho*/
    COORD Ponto_destaque;

    /*Imprime na tela as opções do menu*/
    for(i = 0; i < QTD_STRING; i++)
    {   
        /*Seta o lugar aonde deve ser impresso o menu*/
        gotoxy(coordenadas_Janela.X + tam_opcao_menu + 1, coordenadas_Janela.Y + janela->largura/janela->altura/2);

        /*Foi criada outro tipo COORD para representar a coordenada do destaque da letra de atalho, poderia utilizar-se somente a coordenada atual da janela.
        Mas o código ficaria um pouco confuso*/
        Ponto_destaque.X = wherex();
        Ponto_destaque.Y = wherey();


        /*Verificação da navegação do usuario por meio das teclas direcionais*/
        if(i == op->escolha_do_usuario)
        {
            textcolor(YELLOW);
        }
        
        /*Pegar a posição da onde esta a opção ARQUIVO, depois criar um submenu pra escolha*/

        /*Imprime a string referente a opção do menu*/
        puts(string->menu[i]);

        
        /*Colore a letra quando apertado o 'ALT_ESQUERDO'*/
        if(op->controle_do_alt)
        {
            /*A função strchr retorna um ponteiro com a posição da 1° ocorrência da letra dentro de uma string.*/
            p_posicao_letra = strchr(string->menu[i], letras[i]);

            /*É feito um calculo para pegar a posição inteira da letra na string*/
            pos = p_posicao_letra - string->menu[i];

            /*Com a posição da letra encontrada em mãos, esta é somada com a coordenada atual*/
            gotoxy(Ponto_destaque.X + pos, Ponto_destaque.Y);

            /*Modifica a cor do texto para demostrar o destaque da letra de atalho*/
            textcolor(op->cor_atalho);
            putchar(letras[i]);
           
        }
        
        /*Após imprimir na tela a opção com a cor de navegação padrao do menu, volta-se a cor original do prompt pra nao colorir toda a tela*/
        textcolor(LIGHTGRAY);

        /*O tamanho da opcao armazena o tamanho da string do menu e o soma com a quantidade de espaçamento declarado fixo,
        isso faz com que haja um espaçamento entre as opções do menu independente do tamanho da string */
        tam_opcao_menu += strlen(string->menu[i]) + ESPACAMENTO;

    }
}

/*Função que le o teclado do usuario*/
void Le_Teclado(LE_TECLADO *leitura, USUARIO *op, STRINGS * string)
{

    /*Identifica um 'hit' do teclado*/   
    if(hit(KEYBOARD_HIT))
    {
        /*Atribuição do evento que ocorreu*/
        leitura->tecla = Evento();
        
        /*Verificação caso seja um evento originário do teclado*/
        if(leitura->tecla.tipo_evento & KEY_EVENT)
        {
            /*Precisa ser aqui dentro o controle dos eventos, pois somente se for um evento do teclado, vai ser retornado se vai ou nao ser impresso o menu*/
            op->controla_evento = Mapeia_teclas_Entrada(leitura);

            if(op->controla_evento)
            {
                /*Verificação da tecla se foi liberada ao pressionada*/
                if(leitura->tecla.teclado.status_tecla == LIBERADA)
                {
                    /*O controle da tecla alt esquerda é atribuida em 0 pois a tecla esta solta*/
                    op->controle_do_alt = 0;

                    /*Casos para o menu*/
                    switch(leitura->tecla.teclado.codigo_tecla)
                    {
                        
                        /*Seleciona a opção do menu principal*/
                        case ENTER:
                        {
                            op->controla_evento = 0;
                           
                            /*De acordo com a escolha do usuario, uma das opções sera selecionada*/
                            switch(op->escolha_do_usuario)
                            {
                                /*Caso quando o usuario escolher o submenu arquivo*/
                                case 0:
                                {
                                    /*Chama função para abrir o submenu arquivo*/
                                    Submenu_Arquivo(string);
                                    break;
                                }
                                /*Usuario escolheu modificar a quantidade de caracteres do x para o TAB*/
                                case 2:
                                {

                                    /*Chama a função para pegar o numero dado pelo usuario*/
                                    Caractere_X(leitura, op);
                                    break;
                                }
                            }

                        }

                        /*Setas para navegação do menu*/
                        case SETA_PARA_BAIXO:
                        {
                            break;
                        }
                        case SETA_PARA_CIMA:
                        {
                            break;
                        }

                        /*Navegação à direita*/
                        case SETA_PARA_DIREITA:
                        {
                            
                            /*Foi criado uma variavel para a escolha do usuario para simular a navegação do menu, é necessario somente
                            modificar o valor da própria variavel conforme o usuario aperta as teclas direcionais, a verificação é feita para a navegação
                            ficar limitada entre o intervalo da 1° a ultima opção, o mesmo é feito nas outras setas de direção, porem com verificações distintas*/
                            if(op->escolha_do_usuario >= 0 && op->escolha_do_usuario < QTD_STRING - 1)
                            {
                                op->escolha_do_usuario += 1;
                            }
                            break;
                        }

                        /*Navegação à esquerda*/
                        case SETA_PARA_ESQUERDA:
                        {
                            if(op->escolha_do_usuario > 0 && op->escolha_do_usuario <= QTD_STRING)
                            {
                                op->escolha_do_usuario -= 1;
                            }
                            
                            break;
                        }
                        
                        /*Saida do programa (TEMPORARIO)*/
                        case ESC:
                        {
                            op->esc_apertado -= 1;
                            break;
                        }

                    }
                }
                else
                {
                    /*Casos especificos para teclas de controle*/
                    if(leitura->tecla.teclado.status_teclas_controle & ALT_ESQUERDO)
                    {
                        /*É definido o alt_esquerdo como 1 pois esta sendo pressionado, a cor muda para azul*/
                        op->controle_do_alt = 1;
                        op->cor_atalho = BLUE;

                        /*switch para a outra tecla após o ALT_ESQUERDO*/
                        switch(leitura->tecla.teclado.codigo_tecla)
                        {
                            
                            /*Teclas de atalho somente quando apertar que vou a algum lugar*/
                            case 'A':
                            {
                                gotoxy(2, 30);
                                break;
                            }
                        }
                    }
                }
            }
            
        }
      
    }
}
    



/*Controla os eventos para eu ter controle sobre as teclas de pedido de usurio, por isso é necessario mapear as teclas para imprimir novamente a janela de menu*/
int Mapeia_teclas_Entrada(LE_TECLADO *leitura)
{
    /*Mapeamento de cada tecla*/

    /*Verificação do alt esquerdo pois é uma tecla de controle*/
    if(leitura->tecla.teclado.status_teclas_controle & ALT_ESQUERDO)
    {
        return 1;
    }

    /*Switch para cases de teclas que nao sao de controle*/
    switch(leitura->tecla.teclado.codigo_tecla)
    {
        case SETA_PARA_BAIXO:
        {
            return 1;
        }
        case SETA_PARA_CIMA:
        {
            return 1;
        }
        case SETA_PARA_DIREITA:
        {
            return 1;
        }
        case SETA_PARA_ESQUERDA:
        {
            return 1;
        }
        case ENTER:
        {
            return 1;
        }
        case ESC:
        {
            return 1;
        }

    }
    /*Caso seja qualquer outro tipo de tecla retorna 0, para nao imprimir de novo o menu*/
    return 0;
}


/*Quando a função le teclado for desabilitada, esta função entra para ler os dados do usuario*/
void Caractere_X(LE_TECLADO *leitura, USUARIO *op)
{
    /*Numeros de 2 unidades somente*/
    char numero[2];
    int saida = 1;
    int i = 0;
    op->numero_convertido = 0;
    
    /*Loop ate a conversao ser feita corretamente*/
    while(saida)
    {
            puts("Caractere X: ");
            /*Loop para pegar os numeros inseridos pelo usuario*/
            while(1)
            {
                /*Pega o caractere digitado*/
                leitura->tecla.teclado.codigo_tecla = getch();

                /*Se este caractere é um dígito*/
                if(leitura->tecla.teclado.codigo_tecla >= 48 && leitura->tecla.teclado.codigo_tecla <= 57)
                {
                    /*A cada incremento é colocado o caractere na string numero*/
                    numero[i] = leitura->tecla.teclado.codigo_tecla;

                    /*Impresso na tela para o usuário*/
                    putchar(numero[i]);
                    i++;

                    /*Ao chegar no fim da string, é colocado o '\0'*/
                    if(i == 2)
                    {
                        numero[i] = '\0';

                        /*O numero da string é convertido em um numero inteiro para ser usado no TAB*/
                        op->numero_convertido = atoi(numero);
                        
                        break;
                    }
                    
                }
                else
                {
                    /*Caso nao seja um numero o caractere digitado anteriormente*/
                    puts("Numero invalido!");
                }
            }

            /*Ao passar pela conversao sai do loop interno*/
            saida = 0;
           
        }
    }   


/*Função para apresentar o submenu quando for apertado na opção arquivo*/
void Submenu_Arquivo(STRINGS *string)
{
    /*É criado outro tipo EVENTO para armazenar as teclas da navegação e escolha do submenu arquivo*/
    EVENTO sub_arquivo;
    COORD Submenu;
    int controla_sub = 1;
    int i;
    int saida = 1;

    /*O cursor ja esta localizado abaixo da linha onde é impressa as opções do menu principal, entao pegamos a localização dele para conseguir colocar nossas subopções*/
    Submenu.X = wherex();
    Submenu.Y = wherey();


    /*FAZER ALGUM JEITO DE CONTROLAR AS OPÇÕES DO SUBMENU*************/
    /*Loop pra pegar somente as teclas necessarias*/
    do
    {
        /*Controla a impressao do submenu*/
        if(controla_sub)
        {
            /*Imprime as opções de arquivo*/
            for(i = 0; i <= 1; i++)
            {
                gotoxy(Submenu.X + 1, Submenu.Y + i);
                puts(string->submenu_arquivo[i]);
            }    
        }
        
        /*Armazena os eventos do teclado*/
        sub_arquivo = Evento();

        /*Verifica se é um evento do teclado*/
        if(sub_arquivo.tipo_evento & KEY_EVENT)
        {   
            /*Verifica se foi liberada a tecla*/
            if(sub_arquivo.teclado.status_tecla == LIBERADA)
            {
                /*Qual tecla foi apertada*/
                switch(sub_arquivo.teclado.codigo_tecla)
                {
                    /*Navegação do submenu arquivo*/
                    case SETA_PARA_BAIXO:
                    {
                        break;
                    }
                    
                    case SETA_PARA_CIMA:
                    {
                        
                        break;
                    }
                    
                    /*Saida do loop somente quando ele pressione ESC ou ENTER*/
                    case ESC:
                    {
                        saida = 0;
                        break;
                    }

                    /*Meio de saida do loop e entrada em outra função*/
                    case ENTER:
                    {
                        saida = 0;
                        break;
                    }
                }
            }
        }
    }while(saida);

}