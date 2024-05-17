/*Lógica dos protótipos criados no arquivo 'funcoes.h'*/

/*Bibliotecas/Constantes*/
# include <stdio.h> /*FILE, fopen(), printf(), */
# include <string.h> /*strlen(), strchr()*/
# include <ctype.h>
# include <time.h>
# include "console_v1.5.5.h" /*SETAS_DE_DIREÇÃO*/
# include "conio_v3.2.4.h" /*gotoxy()*/
# include "funcoes.h"

/*Função que abre o arquivo*/
void Abre_Arquivo(STRINGS *string)
{
    EVENTO arquivo;
    int conta_linhas = 0;
    int shift_pressionado = 0;
    char *retorno;

    int i = 0;

    /*Inserir o arquivo desejado para abertura*/
    printf("Insira o arquivo que deseja abrir: ");
    while(1)
    {
        /*Verifica se foi um pressionamento do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            /*Imprime na tela o caractere digitado*/
            arquivo = Evento();
            if(arquivo.tipo_evento & KEY_EVENT)
            {
                /*Verifica se a tecla foi liberada*/
                if(arquivo.teclado.status_tecla == LIBERADA)
                {
                    /*Caso for um ESC sai do loop e volta ao menu padrão*/
                    if(arquivo.teclado.key_code == ESC)
                    {
                        /*Caso se arrependa de digitar volta as opções*/
                        break;
                    }

                    /*Se for um ENTER sai do loop e tenta abrir o arquivo*/
                    if(arquivo.teclado.key_code == ENTER)
                    {
                        string->arquivo_txt[i] = '\0';
                        printf("\n");
                        break;
                    }

                    /*Quando for pressionado o shift, entra nessa condição pra conseguir colocar o caractere correto dentro da string 'arquivo_txt'*/
                    if(shift_pressionado)
                    {
                        /*Verifca se liberou o shift*/
                        if(arquivo.teclado.status_tecla == LIBERADA)
                        {
                            /*A string que representa meu arquivo recebe o caractere proveniente do teclado e o imprime na tela*/
                            string->arquivo_txt[i] = arquivo.teclado.ascii_code;
                            printf("%c", string->arquivo_txt[i]);
                            i++;

                            /*Reseta a variavel para controle do shift se esta ou nao pressionado*/
                            shift_pressionado = 0;
                        }
        
                    }
                    /*Caso normais de teclas diferentes dos shifts*/
                    else
                    {
                        /*Intervalo de caracteres imprimíveis na tela*/
                        if(arquivo.teclado.key_code >= 32 && arquivo.teclado.key_code <= 254)
                        {
                            /*A string que representa o arquivo que sera aberto recebe o caractere dentro do intervalo da condição
                            e imprime-o na tela*/
                            string->arquivo_txt[i] = arquivo.teclado.ascii_code;
                            printf("%c", string->arquivo_txt[i]);
                            i++;
                        }
                        
                    }
                }
            }
        }
                
    }

    /*Verificação do arquivo para o modo leitura*/
    string->arquivo_origem = fopen(string->arquivo_txt, "r+");

    /*Validação da abertura*/
    if(string->arquivo_origem != NULL)
    {
        /*Chamada para a função que conta as linhas do arquivo*/
        string->conta_linhas = Conta_Linhas_Arquivo(string->arquivo_origem);

        /*Volta o cursor na posição inicial do arquivo*/
        fseek(string->arquivo_origem, 0, SEEK_SET);

        /*Aloca memoria para minha matriz*/
        string->matriz_de_linhas = (char **)malloc(string->conta_linhas * sizeof(char *));

        /*Loop para alocar memoria para cada linha do meu arquivo*/
        while(1)
        {
            /*A cada iteração aloca memoria para minha string*/
            string->matriz_de_linhas[string->index_linha_matriz] = (char *)malloc(TAM_BUFFER * sizeof(char));

            /*Retorno do ponteiro para o arquivo*/
            retorno = fgets(string->matriz_de_linhas[string->index_linha_matriz], TAM_BUFFER, string->arquivo_origem);

            /*Se for final do arquivo, sai do loop*/
            if(retorno == NULL)
            {
                break;  
            }

            string->index_linha_matriz++;
        }

        /*Limpa a tela pois preciso limpar a mensagem de compilamento inicial*/
        clrscr();
        fclose(string->arquivo_origem);

        /*Função para escrita no arquivo*/
        Escreve_no_Arquivo(string);
        
    }
    else
    {
        /*Erro na abertura do arquivo*/
        printf("Abertura do arquivo deu errado!");
    }
    
    
        /*Libera 1° a memoria alocada para as linhas*/  
        for(i = 0; i < conta_linhas; i++)
        {
            free(string->matriz_de_linhas[i]);
        }


        /*Limpa a memoria que foi alocada para a matriz*/
        free(string->matriz_de_linhas);    

        
    
}

/*Conta as linhas do arquivo*/
int Conta_Linhas_Arquivo(FILE *arquivo_origem)
{
    char caractere;
    int contador = 0;

    /*Percorre o arquivo e conta suas linhas*/
    do
    {
        caractere = fgetc(arquivo_origem);
        if(caractere == '\n' || caractere == EOF)
        {
            contador++;
        }
    }while(caractere != EOF);

    return contador;
}

/*Função para escrita no arquivo*/
void Escreve_no_Arquivo(STRINGS *string)
{
    EVENTO evento_para_escrita;
    int esc_pressionado = 1;
    int i, j = 0;
    int tamanho_por_bloco = BLOCO_DE_IMPRESSAO;


    /*Variaveis para mover o cursor ao abrir o arquivo*/
    int move_cursor_linha = 0;
    int move_cursor_coluna = 0;
    
    gotoxy(1,1);
    
    /*Pega a posição atual do meu cursor*/
    string->posicao_cursor_escrita.X = wherex();
    string->posicao_cursor_escrita.Y = wherey();


    /*O ERRO ESTA AQUI! Tentar fazer a impressão por blocos quando atingir o final do 1° bloco e assim em diante
    Fazer impressão por blocos de linhas para não misturar com o prompt de comando*/
    for(i = 0; i < string->conta_linhas; i += BLOCO_DE_IMPRESSAO)
    {
        for(j = i; j < BLOCO_DE_IMPRESSAO; j++)
        {
            printf("%s", string->matriz_de_linhas[j]);    
        }
    }
    gotoxy(1,1);

    /*Loop para pegar os eventos do teclado, no caso os caracteres imprimivei para serem colocado no arquivo*/
    do
    {
        /*Pega uma ação do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            /*Pega o evento de origem do teclado*/
            evento_para_escrita = Evento();

            /*Verifica se é um evento do teclado*/
            if(evento_para_escrita.tipo_evento & KEY_EVENT)
            {
                /*tecla pressionada ou não */
                if(evento_para_escrita.teclado.status_tecla == LIBERADA)
                {
                    /*Casos para cada tecla*/
                    switch(evento_para_escrita.teclado.key_code)
                    {
                        /*Navegação no arquivo usando o cursor*/
                        case SETA_PARA_DIREITA:
                        {
                            /*Verificação para não ultrapassar o fim da linha, ao estar dentro do intervalo é incrementado o cursor, o '\0' é justamente para o fim da ultima linha, ja que ela nao contem '\n'*/
                            if(string->matriz_de_linhas[move_cursor_coluna][move_cursor_linha] != '\n' && string->matriz_de_linhas[move_cursor_coluna][move_cursor_linha] != '\0')
                            {
                                /*Posiciona o cursor*/
                                move_cursor_linha += 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_linha, string->posicao_cursor_escrita.Y + move_cursor_coluna);
                                
                            }
                            break;
                        }

                        case SETA_PARA_ESQUERDA:
                        {
                            /*Verificação para a movimentação do cursor não ser menor do que o inicio da coordenada do meu arquivo*/
                            if(move_cursor_linha >= string->posicao_cursor_escrita.X)
                            {
                                /*Posiciona o meu cursor quando ando para atrás*/
                                move_cursor_linha -= 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_linha, string->posicao_cursor_escrita.Y + move_cursor_coluna);
                            }
                            break;
                        }
                        
                        case SETA_PARA_BAIXO:
                        {
                            /*Verifica o tamanho das linhas do meu arquivo, caso chegue na linha final não consigo ultrapassa-la*/
                            if(move_cursor_coluna < tamanho_por_bloco)
                            {  
                                /*A linha zera para que eu possa andar pelas linhas até o '\n' dela*/
                                move_cursor_linha = 0;
                                move_cursor_coluna += 1;
                                gotoxy(string->posicao_cursor_escrita.X, string->posicao_cursor_escrita.Y + move_cursor_coluna);
                            }
                            else
                            {
                                /*Quando a coluna passar do limite do bloco de impressao de linhas
                                soma-se a variavel 'tamanho_por_bloco' com uma constante que sera o limite maximo de impressao de linhas,
                                isso é passado novamente para o loop que faz as impressoes das linhas
                                if(move_cursor_coluna > tamanho_por_bloco)
                                {
                                    tamanho_por_bloco += BLOCO_DE_IMPRESSAO;
                                }*/
                            }
                            
                            break;
                        }

                        case SETA_PARA_CIMA:
                        {
                            /*Ao subir com o cursor nao pode ultrapassar a 1° linha*/
                            if(move_cursor_coluna >= string->posicao_cursor_escrita.X)
                            {
                                /*Zera o 'move_cursor_linha' para que eu possa andar pela outra linha normalmente*/
                                move_cursor_linha = 0;
                                move_cursor_coluna -= 1;
                                gotoxy(string->posicao_cursor_escrita.X, string->posicao_cursor_escrita.Y + move_cursor_coluna);
                            }
                    
                            break;
                        }

                        /*Sobrescreve caracteres*/
                        case INSERT:
                        {
                            
                            break;
                        }

                        /*Sai do loop*/
                        case ESC:
                        {
                            move_cursor_linha = 0;
                            move_cursor_coluna = 0;
                            esc_pressionado = 0;
                            break;
                        }
                    }
                }
            }
        }
    }while(esc_pressionado);
    
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
    for(i = 0; i < LARGURA; i++)
    {
        gotoxy(janela->coordenadas_janela.X + i, janela->coordenadas_janela.Y);
        printf("=");
    }

    /*Coluna esquerda*/
    for(i = 0; i < ALTURA; i++)
    {
        gotoxy(janela->coordenadas_janela.X, janela->coordenadas_janela.Y + i);
        printf("|");
    }

    /*Linha inferior*/
    for(i = 0; i < LARGURA; i++)
    {
        /*Necessário o incremento do i em 1, para nao borrar o '|' da coluna esquerda,
        há de se decrementar a janela->altura pois o printf da um quebra linha, para isso imprimir o caractere '=' uma linha depois, se decrementa o y*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + LARGURA - 1);
        printf("=");
    }

    /*Coluna Direita*/
    for(i = 0; i < ALTURA; i++)
    {
        /*X recebe o valor da largura, assim eu tenho a coordenada do fim da linha superior, feito isso, somente incrementar o y até a altura
        definida*/
        gotoxy(janela->coordenadas_janela.X + LARGURA, janela->coordenadas_janela.Y + i);
        printf("|");
    }

    /*Linha inferior a linha superior*/
    /*A largura é decrementada pois passa do limite da coluna direita*/
    for(i = 0; i < LARGURA - 1; i++)
    {
        /*Dividindo a largura e altura e, somando com a coordenadas_Janela.Y, tenho o lugar para imprimir a linha inferior a superior,
        somente é necessário incrementar o x, x + 1 pois ele 'come' a coluna da esquerda, para ajustar incrementei em +1 e decrementei a largura na condição de parada*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + LARGURA/ALTURA);
        printf("=");
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
        gotoxy(janela->coordenadas_janela.X + tam_opcao_menu + 1, janela->coordenadas_janela.Y + LARGURA/ALTURA/2);

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

            /*Cor para somente simular uma navegação entre as opções*/
            textcolor(YELLOW);
        }

        /*Imprime a string referente a opção do menu*/
        printf("%s", string->menu[i]);

        
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
            printf("%c", letras[i]);
           
        }
        
        /*Após imprimir na tela a opção com a cor de navegação padrao do menu, volta-se a cor original do prompt pra nao colorir toda a tela*/
        textcolor(string->cores_texto);

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
                    switch(leitura->tecla.teclado.key_code)
                    {
                        
                        /*Seleciona a opção do menu principal*/
                        case ENTER:
                        {
                           
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
                                    /*Chama a função para o submenu de cor de fundo*/
                                    Submenu_background(string, op);
                                    break;
                                }

                                /*Caso para trocar a cor de texto*/
                                case 4:
                                {
                                    /*Chama a função para o submenu de cor de texto*/
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
                        switch(leitura->tecla.teclado.key_code)
                        {
                            /*Uma ideia aqui é criar um vetor de coordenadas, há o erro de ao estar em uma opção, ele nao me redireciona aquela opção,
                            ao chamar arquivo, estando em altera x, o submenu aparece abaixo de altera x e não abaixo do arquivo, onde é o submenu correspondente*/


                            /*Os gotoxy() são para setar a coordenada correspondente ao lugar aonde será impresso o submenu de cada opção do menu principal*/
                            /*Teclas de atalho para chamada das opções do menu principal*/
                            /*Atalho para opção 'ARQUIVO'*/
                            case 'A':
                            {
                                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y);

                                /*Chama a função para a abertura do arquivo*/
                                Submenu_Arquivo(string, op);
                                break;
                            }
                            
                            /*Atalho para opção 'ALINHAMENTO'*/
                            case 'L':
                            {
                                break;
                            }

                            /*Atalho para opção 'ALTERAR X'*/
                            case 'X':
                            {
                                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y);

                                /*Chama a função para o caractere TAB*/
                                Caractere_X(leitura, op);
                                break;
                            }

                            /*Atalho para opção 'COR FUNDO'*/
                            case 'F':
                            {
                                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y);

                                /*Chamada da função para trocar a cor de fundo*/
                                Submenu_background(string, op);
                                break;
                            }

                            /*Atalho para opção 'COR TEXTO'*/
                            case 'T':
                            {
                                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y);

                                /*Chamada para a função que troca a cor de texto*/
                                Submenu_cor_texto(string, op);
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
    switch(leitura->tecla.teclado.key_code)
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
                leitura->tecla.teclado.key_code = getch();

                /*Se este caractere é um dígito*/
                if(leitura->tecla.teclado.key_code >= 48 && leitura->tecla.teclado.key_code <= 57)
                {
                    /*A cada incremento é colocado o caractere na string numero*/
                    numero[i] = leitura->tecla.teclado.key_code;

                    /*Impresso na tela para o usuário*/
                    printf("%c", numero[i]);
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
                printf("%s", string->submenu_arquivo[i]);
                textcolor(string->cores_texto);
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
                switch(sub_arquivo.teclado.key_code)
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

                            /*Usuario optou pra salvar o arquivo aberto*/
                            case 1:
                            {
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
            for(i = 0; i < 16; i++)
            {
                if(i == escolhas_setas_background)
                {
                    textcolor(YELLOW);
                }
                /*Imprime as opções do submenu no devido lugar graças a coordenada que foi pega na função onde imprime as opções principais do menu*/
                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + i + 1);
                printf("%s", string->submenu_cores[i]);
                textcolor(string->cores_texto);
            }
            controla_sub_cor = 0;
        }

        /*Pega os eventos do teclado*/
        sub_cor_fundo = Evento();
        
        if(sub_cor_fundo.tipo_evento & KEY_EVENT)
        {
            if(sub_cor_fundo.teclado.status_tecla == LIBERADA)
            {
                switch(sub_cor_fundo.teclado.key_code)
                {
                    /*Navegação no menu cores de fundo*/
                    case SETA_PARA_CIMA:
                    {
                        if(escolhas_setas_background > 0 && escolhas_setas_background < 16)
                        {
                            escolhas_setas_background -= 1;
                            controla_sub_cor = 1;
                        }
                        break;
                    }

                    case SETA_PARA_BAIXO:
                    {
                        if(escolhas_setas_background >= 0 && escolhas_setas_background < 15)
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
                        op->imprime_janela_cor_diferente = 1;
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
            for(i = 0; i < 16; i++)
            {
                if(i == escolhas_setas_cor_texto)
                {
                    textcolor(YELLOW);
                }
                gotoxy(op->coordenadas_submenus.X, op->coordenadas_submenus.Y + i + 1);
                printf("%s", string->submenu_cores[i]);
                textcolor(string->cores_texto);
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
                switch(cor_texto.teclado.key_code)
                {
                    /*Navegação do submenu de troca de cor do texto*/
                    case SETA_PARA_CIMA:
                    {
                        if(escolhas_setas_cor_texto > 0 && escolhas_setas_cor_texto < 16)
                        {
                            escolhas_setas_cor_texto -= 1;
                            controla_sub_cor_texto = 1;
                        }
                        break;
                    }

                    case SETA_PARA_BAIXO:
                    {
                        if(escolhas_setas_cor_texto >= 0 && escolhas_setas_cor_texto < 15)
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
                        string->cores_texto = escolhas_setas_cor_texto;
                        op->imprime_janela_cor_diferente = 1;
                        saida = 0;
                        break;
                    }
                }
            }
        }
    }
}
    