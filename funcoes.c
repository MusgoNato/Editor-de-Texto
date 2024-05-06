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
    char arquivo;
    int i = 0;

    /*Insirir o arquivo desejado para abertura*/
    printf("Insira o arquivo que deseja abrir: ");
    while(1)
    {
        if(kbhit())
        {
            arquivo = getche();
            if(arquivo == ESC)
            {
                /*Caso se arrependa de digitar volta as opções*/
                break;
            }
            if(arquivo == ENTER)
            {
                string->arquivo_txt[i] = '\0';
                break;
            }
            else
            {
                if(arquivo >= 33 && arquivo <= 126)
                {
                    string->arquivo_txt[i] = arquivo;
                    i++;
                }
            }
        }
        
        
    }

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
void Copiar_caracteres_pra_matrizes(STRINGS *string, char **opcoes, char **submenu_op_arquivo, char **submenu_op_cor)
{
    int i;
    /*Copio os caracteres de uma string para usar em uma matriz de caractere,
    assim eu posso imprimir uma string inteira somente com a sua posição na matriz e não caractere por caractere*/
    for(i = 0; i < QTD_STRING; i++)
    {
        strcpy(string->menu[i], opcoes[i]);
    }

    /*Loop para as 2 opções do submenu 'ARQUIVO'*/
    for(i = 0; i <= 1; i++)
    {
        strcpy(string->submenu_arquivo[i], submenu_op_arquivo[i]);
    }

    /*Loop para as 16 cores do submenu 'COR FUNDO'*/
    for(i = 0; i <= 16; i++)
    {
        strcpy(string->submenu_cores[i], submenu_op_cor[i]);
    }
}

/*Desenha minha janela do menu*/
void Desenha_Janela_Menu(TAM_JANELA *janela)
{
    int i;
    
    /*Desenha a linha superior do menu*/
    for(i = 0; i < janela->largura; i++)
    {
        gotoxy(janela->coordenadas_janela.X + i, janela->coordenadas_janela.Y);
        putchar('=');
    }

    /*Coluna esquerda*/
    for(i = 0; i < janela->altura; i++)
    {
        gotoxy(janela->coordenadas_janela.X, janela->coordenadas_janela.Y + i);
        putchar('|');
    }

    /*Linha inferior*/
    for(i = 0; i < janela->largura; i++)
    {
        /*Necessário o incremento do i em 1, para nao borrar o '|' da coluna esquerda,
        há de se decrementar a janela->altura pois o printf da um quebra linha, para isso imprimir o caractere '=' uma linha depois, se decrementa o y*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + janela->altura - 1);
        putchar('=');
    }

    /*Coluna Direita*/
    for(i = 0; i < janela->altura; i++)
    {
        /*X recebe o valor da largura, assim eu tenho a coordenada do fim da linha superior, feito isso, somente incrementar o y até a altura
        definida*/
        gotoxy(janela->coordenadas_janela.X + janela->largura, janela->coordenadas_janela.Y + i);
        putchar('|');
    }

    /*Linha inferior a linha superior*/
    /*A largura é decrementada pois passa do limite da coluna direita*/
    for(i = 0; i < janela->largura - 1; i++)
    {
        /*Dividindo a largura e altura e, somando com a coordenadas_Janela.Y, tenho o lugar para imprimir a linha inferior a superior,
        somente é necessário incrementar o x, x + 1 pois ele 'come' a coluna da esquerda, para ajustar incrementei em +1 e decrementei a largura na condição de parada*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + janela->largura/janela->altura);
        putchar('=');
    }
    
}



/*Função que imprime as opções de menu na tela*/
void Imprime_op_Menu(TAM_JANELA *janela, STRINGS *string, USUARIO *op, char *letras)
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
        gotoxy(janela->coordenadas_janela.X + tam_opcao_menu + 1, janela->coordenadas_janela.Y + janela->largura/janela->altura/2);

        /*Foi criada outro tipo COORD para representar a coordenada do destaque da letra de atalho, poderia utilizar-se somente a coordenada atual da janela.
        Mas o código ficaria um pouco confuso*/
        Ponto_destaque.X = wherex();
        Ponto_destaque.Y = wherey();


        /*Verificação da navegação do usuario por meio das teclas direcionais*/
        if(i == op->escolha_do_usuario)
        {
            /*Quando uma opção for selecionada, eu tenho a coordenada dela para imprimir o submenu dessa opção, caso precise*/
            op->coordenadas_submenus.X = wherex();
            op->coordenadas_submenus.Y = wherey();

            /*Cor para somente para simular uma navegação entre as opções*/
            textcolor(YELLOW);
        }

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
                                    Submenu_Arquivo(string, op);
                                    break;
                                }

                                /*Caso para alinhar o texto*/
                                case 1:
                                {
                                    break;
                                }

                                /*Usuario escolheu modificar a quantidade de caracteres do x para o TAB*/
                                case 2:
                                {

                                    /*Chama a função para pegar o numero dado pelo usuario*/
                                    Caractere_X(leitura, op);
                                    break;
                                }

                                /*Caso para trocar a cor de fundo*/
                                case 3:
                                {
                                    Submenu_background(string, op);
                                    break;
                                }

                                /*Caso para trocar a cor de texto*/
                                case 4:
                                {
                                    Submenu_cor_texto(string, op);
                                    break;
                                }
                            }

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
                        
                        /*Saida do programa*/
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
    
    /*Coloca a coordenada da onde deve ser impresso, o caso abaixo da opção do menu principal 'CARACTERE X'*/
    gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + 1);

    /*Loop ate a conversao ser feita corretamente*/
    while(saida)
    {
            printf("Caractere X: ");
            /*Loop para pegar os numeros inseridos pelo usuario*/
            while(1)
            {
                /*Pega o caractere digitado sem aparecer na tela*/
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
                    printf("Numero invalido!");
                }
            }

            /*Ao passar pela conversao sai do loop interno*/
            saida = 0;
           
        }
    }   


/*Função para apresentar o submenu quando for apertado na opção arquivo*/
void Submenu_Arquivo(STRINGS *string, USUARIO *op)
{
    /*É criado outro tipo EVENTO para armazenar as teclas da navegação e escolha do submenu arquivo*/
    EVENTO sub_arquivo;
    int i;
    int saida = 1;
    int controla_sub = 1;
    int escolha_setas_submenu = 0;

    /*Loop pra pegar somente as teclas necessarias*/
    while(saida)
    {
        /*Controla a impressao do submenu*/
        if(controla_sub)
        {
            /*Imprime as opções de arquivo*/
            for(i = 0; i <= 1; i++)
            {
                if(i == escolha_setas_submenu)
                {
                    textcolor(YELLOW);
                }
                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + i + 1);
                puts(string->submenu_arquivo[i]);
                textcolor(LIGHTGRAY);
            }    
            /*Só é necessario imprimir uma 1° vez, caso o usuario pressione as teclas de navegação, ai a variavel volta com seu valor 1, caso nao continua zerado*/
            controla_sub = 0;
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
                        /*Navegação do submenu na opção arquivo*/
                        if(escolha_setas_submenu >= 0 && escolha_setas_submenu < 1)
                        {
                            escolha_setas_submenu += 1;
                            controla_sub = 1;
                        }
                        break;
                    }
                    
                    case SETA_PARA_CIMA:
                    {
                        if(escolha_setas_submenu > 0 && escolha_setas_submenu <= 1)
                        {
                            escolha_setas_submenu -= 1;
                            controla_sub = 1;
                        }
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
                        /*Ao apertar o enter, é aonde a posição 'escolha_estas_submenu' vai estar, entao eu tenho controle de qual opção sera selecionada somente
                        com uma variavel*/
                        switch(escolha_setas_submenu)
                        {

                            /*Usuario optou por abrir um arquivo*/
                            case 0:
                            {
                                /*Chama a função para abrir o arquivo*/
                                Abre_Arquivo(string);
                                saida = 0;
                                controla_sub = 0;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

}

/*Função para imprimir os submenus da opção 'COR FUNDO'*/
void Submenu_background(STRINGS *string, USUARIO *op)
{
    EVENTO sub_cor_fundo;
    int i = 0;
    int saida = 1;
    int controla_sub_cor = 1;
    int escolhas_setas_background = 0;

    /*Pega os eventos do teclado para navegar entre as opções do menu*/
    while(saida)
    {  
        if(controla_sub_cor)
        {
            /*Imprime as 16 cores do submenu*/
            for(i = 0; i <= 16; i++)
            {
                if(i == escolhas_setas_background)
                {
                    textcolor(YELLOW);
                }
                /*Imprime as opções do submenu no devido lugar graças a coordenada que foi pega na função onde imprime as opções principais do menu*/
                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + i + 1);
                puts(string->submenu_cores[i]);
                textcolor(LIGHTGRAY);
            }
            controla_sub_cor = 0;
        }

        /*Pega os eventos do teclado*/
        sub_cor_fundo = Evento();
        
        if(sub_cor_fundo.tipo_evento & KEY_EVENT)
        {
            if(sub_cor_fundo.teclado.status_tecla == LIBERADA)
            {
                switch(sub_cor_fundo.teclado.codigo_tecla)
                {
                    /*Navegação no menu cores*/
                    case SETA_PARA_CIMA:
                    {
                        if(escolhas_setas_background > 0 && escolhas_setas_background <= 16)
                        {
                            escolhas_setas_background -= 1;
                            controla_sub_cor = 1;
                        }
                        break;
                    }

                    case SETA_PARA_BAIXO:
                    {
                        if(escolhas_setas_background >= 0 && escolhas_setas_background < 16)
                        {
                            escolhas_setas_background += 1;
                            controla_sub_cor = 1;
                        }
                        break;
                    }

                    case ESC:
                    {
                        saida = 0;
                        break;
                    }

                    /*Ao apertar enter ele sai do loop e volta a ler o teclado novamente*/
                    case ENTER:
                    {
                        string->cores_background = escolhas_setas_background;
                        saida = 0;
                        break;
                    }
                }
            }   
        }
    }
}


/*Muda a cor do texto de fundo*/
void Submenu_cor_texto(STRINGS *string, USUARIO *op)
{
    EVENTO cor_texto;
    int i = 0;
    int saida = 1;
    int controla_sub_cor_texto = 1;
    int escolhas_setas_cor_texto = 0;

    /*Loop*/
    while(saida)
    {
        if(controla_sub_cor_texto)
        {
            for(i = 0; i <= 16; i++)
            {
                if(i == escolhas_setas_cor_texto)
                {
                    textcolor(YELLOW);
                }
                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + i + 1);
                puts(string->submenu_cores[i]);
                textcolor(LIGHTGRAY);
            }
            controla_sub_cor_texto = 0;
        }

        /*Pega os eventos da teclado*/
        cor_texto = Evento();
        if(cor_texto.tipo_evento & KEY_EVENT)
        {
            /*verifica a liberação da tecla*/
            if(cor_texto.teclado.status_tecla == LIBERADA)
            {
                switch(cor_texto.teclado.codigo_tecla)
                {
                    case SETA_PARA_CIMA:
                    {
                        if(escolhas_setas_cor_texto > 0 && escolhas_setas_cor_texto <= 16)
                        {
                            escolhas_setas_cor_texto -= 1;
                            controla_sub_cor_texto = 1;
                        }
                        break;
                    }

                    case SETA_PARA_BAIXO:
                    {
                        if(escolhas_setas_cor_texto >= 0 && escolhas_setas_cor_texto < 16)
                        {
                            escolhas_setas_cor_texto += 1;
                            controla_sub_cor_texto = 1;
                        }
                        break;
                    }
                    
                    /*Saida do programa*/
                    case ESC:
                    {
                        saida = 0;
                        break;
                    }

                    /*Escolheu tal cor*/
                    case ENTER:
                    {
                        saida = 0;
                        break;
                    }
                }
            }
        }
    }
}