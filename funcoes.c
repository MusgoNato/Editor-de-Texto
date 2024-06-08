/*L?gica dos prot?tipos criados no arquivo 'funcoes.h'*/

/*Bibliotecas/Constantes*/
# include <stdio.h> /*atoi(), fclose(), fgetc(), fopen(), free(), fseek(), maloc(), printf(), putchar() */
# include <string.h> /*strchr(), strcpy(), strlen(), memmove()*/
# include "console_v1.5.5.h" /*Evento(), hit(), tamanhoJanelaConsole(), */
# include "conio_v3.2.4.h" /*clrscr(), getch(), gotoxy(), wherex(), wherey(), textcolor()*/
# include "funcoes.h" /*Abre_Arquivo(), Caractere_X(), Copiar_caracteres_pra_matrizes(), Pega_Caracteres_do_arquivo(),
Escreve_Arquivo(), Desenha_Janela_Menu(), Imprime_op_Menu(), Inicializacao_Variaveis(), Le_Teclado(), Mapeia_teclas_Entrada(), Submenu_Arquivo().
Submenu_background(), Submenu_cor_texto()*/

/*Fun??o que abre o arquivo*/
void Abre_Arquivo(STRINGS *string)
{
    EVENTO arquivo;
    int i = 0;
    char *retorno;
    int controla_arquivo = 0;

    /*Aloca??o da matriz de linhas para NULL
    string->matriz_de_linhas = NULL;*/

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
                    /*Caso for um ESC sai do loop e volta ao menu padr?o*/
                    if(arquivo.teclado.key_code == ESC)
                    {
                        /*Caso se arrependa de digitar volta as op??es*/
                        controla_arquivo = 0;
                        break;
                    }

                    /*Se for um ENTER sai do loop e tenta abrir o arquivo*/
                    if(arquivo.teclado.key_code == ENTER)
                    {
                        string->arquivo_txt[i] = '\0';
                        controla_arquivo = 1;
                        break;
                    }

                    /*Caso seja a tecla backspace, deve voltar, ? decrementado o indice 'i' e colocado o espa?o em branco na string do arquivo .txt*/
                    if(arquivo.teclado.key_code == BACKSPACE)
                    {
                        /*Verifica??o, somente entra caso o indice tenha algum caractere na string*/
                        if(i > 0)
                        {                            
                            /*Pego o backspace pressionado*/
                            string->arquivo_txt[i] = arquivo.teclado.key_code;

                            /*Move o cursor uma posi??o atras no terminal e coloca um espa?o em branco na posi??o anterior antes de mover*/
                            printf("\b ");
                            putchar(string->arquivo_txt[i]);

                            /*recebe um espa?o em branco pois caso o arquivo contenha o numero da tecla BACKSPACE, ir? entrar no arquivo, mesmo supostamente tendo apagado do terminal,
                            porem nao apaga da string, colocando um espa?o garante que na string conter? o espa?o e n?o sera apenas apagado do terminal*/
                            string->arquivo_txt[i] = ' ';

                            /*Decremento o indice para pegar a proxima tecla na posi??o correta*/
                            i--;
                        }
                    }

                    /*Verifica??o do intervalo das teclas*/
                    if((arquivo.teclado.key_code > 45 && arquivo.teclado.key_code <= 254) || arquivo.teclado.key_code == ' ')
                    {
                        /*Pego o caractere correspondente a tabela ascii da tecla pressionada*/
                        arquivo.teclado.key_code = arquivo.teclado.ascii_code;
                        string->arquivo_txt[i] = arquivo.teclado.key_code; 
                        putchar(arquivo.teclado.ascii_code);

                        /*Incrementa para a pr?xima tecla*/
                        i++;
                    }

                }
            }
        }
                
    }

    /*Verifica se caso o usuario aperte ESC, o programa sai para ir as outras op??es do menu, n?o ? necessario criar outro arquivo se o usuario nem apertou ENTER,
    entao somente quando ele aperte ENTER, o arquivo ? criado e verificado*/
    if(controla_arquivo)
    {
        /*Abertura do arquivo para o modo adi??o (append)*/
        string->arquivo_origem = fopen(string->arquivo_txt, "a+");

        /*Como o modo append coloca o ponteiro para o arquivo no final dele, ? recolocado o mesmo para posi??o incial*/
        fseek(string->arquivo_origem, 0, SEEK_SET);

        /*Valida??o da abertura*/
        if(string->arquivo_origem != NULL)
        {
            /*Chamada para a fun??o que conta as linhas do arquivo*/
            string->caracteres_no_arquivo = Pega_caracteres_do_arquivo(string->arquivo_origem);

            /*Como ? append, volta ao cursor no come?o do arquivo*/
            fseek(string->arquivo_origem, 0, SEEK_SET);

            /*Aloca memoria para minha matriz de acordo com a quantidade de caracteres contados anteriormente pela fun??o 'Pega_caracteres_do_arquivo'*/
            string->matriz_de_linhas = (char **)malloc(string->caracteres_no_arquivo * sizeof(char *));

            /*Se a aloca??o der certo entra no loop*/
            if(string->matriz_de_linhas != NULL)
            {
                /*Coloca o cursor no come?o da janela*/
                gotoxy(1,1);

                /*Loop para alocar memoria para cada linha do meu arquivo*/
                while(1)
                {
                    /*A cada itera??o aloca memoria para minha string*/
                    string->matriz_de_linhas[string->index_linha_matriz] = (char *)malloc(TAM_BUFFER * sizeof(char));

                    /*Se caso a aloca??o der certo continua o loop, caso der errado fecha o arquivo, limpa a memoria alocada e sai do loop*/
                    if(string->matriz_de_linhas[string->index_linha_matriz] == NULL)
                    {
                        /*Fecha o arquivo e libera mem?ria*/
                        fclose(string->arquivo_origem);
                        free(string->matriz_de_linhas[string->index_linha_matriz]);
                        break;
                    }

                    /*Retorno do ponteiro para o arquivo*/
                    retorno = fgets(string->matriz_de_linhas[string->index_linha_matriz], TAM_BUFFER, string->arquivo_origem);

                    /*Se for final do arquivo, sai do loop*/
                    if(retorno == NULL)
                    {
                        break;  
                    }

                    /*Incrementa o indice da minha matriz, indo linha por linha*/
                    string->index_linha_matriz++;
                    
                }
            }

            /*Fun??o para escrita no arquivo*/
            Escreve_no_Arquivo(string);
        }
        else
        {
            /*Erro na abertura do arquivo*/
            printf("Abertura do arquivo deu errado!");
        }
    }
    
}

/*Quando a fun??o le teclado for desabilitada, esta fun??o entra para ler os dados do usuario*/
void Caractere_X(LE_TECLADO *leitura, USUARIO *op, STRINGS *string)
{
    /*Numeros de 2 unidades somente*/
    char numero[2];
    int saida = 1;
    int i = 0;
    op->numero_TAB_X = 0;
    
    /*Seta na coordenada correta de onde est? minha op??o no menu*/
    gotoxy(string->vetor_cord_menu[2].X, string->vetor_cord_menu[2].Y + 1);

    /*Loop ate a conversao ser feita corretamente*/
    while(saida)
    {
            printf("Caractere X: ");
            /*Loop para pegar os numeros inseridos pelo usuario*/
            while(1)
            {
                /*Pega o caractere digitado sem aparecer na tela*/
                leitura->tecla.teclado.key_code = getch();

                /*Se este caractere ? um d?gito no intervalo definido*/
                if(leitura->tecla.teclado.key_code >= '0' && leitura->tecla.teclado.key_code <= '9')
                {
                    /*A cada incremento ? colocado o caractere na string numero*/
                    numero[i] = leitura->tecla.teclado.key_code;

                    /*Impresso na tela para o usu?rio*/
                    printf("%c", numero[i]);
                    i++;

                    /*Ao chegar no fim da string, ? colocado o '\0'*/
                    if(i == 2)
                    {
                        numero[i] = '\0';

                        /*O numero da string ? convertido em um numero inteiro para ser usado no TAB*/
                        op->numero_TAB_X = atoi(numero);
                        
                        break;
                    }
                }
            }

            /*Ao passar pela conversao sai do loop interno*/
            saida = 0;
           
        }
    } 

/*Converete a string nas suas devidas posi??es*/
void Copiar_caracteres_pra_matrizes(STRINGS *string, char **opcoes, char **submenu_op_arquivo, char **submenu_op_cor)
{
    int i;

    /*Copio os caracteres de uma string para usar em uma matriz de caractere,
    assim eu posso imprimir uma string inteira somente com a sua posi??o na matriz e n?o caractere por caractere*/
    for(i = 0; i < QTD_STRING; i++)
    {
        strcpy(string->menu[i], opcoes[i]);
    }

    /*Loop para as 2 op??es do submenu 'ARQUIVO'*/
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

/*Pega todos os caracteres do arquivo aberto para alocar na minha matriz de linhas posteriormente*/
int Pega_caracteres_do_arquivo(FILE *arquivo_origem)
{
    char caractere;
    int contador = 0;

    /*Percorre o arquivo e pega cada caractere dentro dele*/
    do
    {
        /*Pega cada caractere do arquivo*/
        caractere = fgetc(arquivo_origem);

        /*Verifica se chegou ao fim do arquivo, preciso pegar caractere por caractere para armazenar na minha matriz de string, necessito de todos os caracteres do arquivo para isso*/
        if(caractere == EOF)
        {
            break;
        }
        else
        {
            contador++;
        }
        
    }while(caractere != EOF);

    /*Retorna a quantidade de caracteres que foram contados no arquivo*/
    return contador;
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
        /*Necess?rio o incremento do i em 1, para nao borrar o '|' da coluna esquerda,
        h? de se decrementar a janela->altura pois o printf da um quebra linha, para isso imprimir o caractere '=' uma linha depois, se decrementa o y*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + LARGURA - 1);
        printf("=");
    }

    /*Coluna Direita*/
    for(i = 0; i < ALTURA; i++)
    {
        /*X recebe o valor da largura, assim eu tenho a coordenada do fim da linha superior, feito isso, somente incrementar o y at? a altura
        definida*/
        gotoxy(janela->coordenadas_janela.X + LARGURA, janela->coordenadas_janela.Y + i);
        printf("|");
    }

    /*Linha inferior a linha superior*/
    /*A largura ? decrementada pois passa do limite da coluna direita*/
    for(i = 0; i < LARGURA - 1; i++)
    {
        /*Dividindo a largura e altura e, somando com a coordenadas_Janela.Y, tenho o lugar para imprimir a linha inferior a superior,
        somente ? necess?rio incrementar o x, x + 1 pois ele 'come' a coluna da esquerda, para ajustar incrementei em +1 e decrementei a largura na condi??o de parada*/
        gotoxy(janela->coordenadas_janela.X + i + 1, janela->coordenadas_janela.Y + LARGURA/ALTURA);
        printf("=");
    }
    
}

/*Fun??o para escrita no arquivo*/
void Escreve_no_Arquivo(STRINGS *string)
{
    EVENTO evento_para_escrita;
    int esc_pressionado = 1;
    int ultima_linha = 0;
    int cursor_final_linha = 0;
    int limite_a_ser_impresso = 0;
    /*nt tamanho = 0;*/
    int i;

    /*Variaveis para mover o cursor ao abrir o arquivo*/
    int move_cursor_na_coluna = 0;
    int move_cursor_na_linha = 0;
    
    /*Pega a posi??o atual do meu cursor*/
    string->posicao_cursor_escrita.X = wherex();
    string->posicao_cursor_escrita.Y = wherey();

    /*Guarda a metade do tamanho maximo da minha janela*/
    limite_a_ser_impresso += string->limite_maximo_Janela.Y/2;

    /*Impress?o das linhas do meu arquivo*/
    /*O index linha matriz ser? um contador de quntas linhas eu tenho no meu arquivo, pois na abertura dele, no momento da aloca??o ele serve de indice para acesso a cada linha,
    ent?o pode servir de limite pois guarda a ultima linha contada*/
    for(i = 0; i < string->index_linha_matriz; i++)
    {
        /*Aqui vai ser o local para ser impresso o meu arquivo, que ficar  abaixo da linha do menu principal*/
        gotoxy(string->posicao_cursor_escrita.X, string->limite_maximo_Janela.Y/2 + i);

        /*A variavel limite a ser impresso guarda o valor do tamanho maximo da janela dividido por 2, me proporciona a metade da janela,
        assim eu tenho o limite de imprimir o meu arquivo*/
        if(i <= limite_a_ser_impresso)
        {
            /*Imprime cada linha do arquivo*/
            printf("%s", string->matriz_de_linhas[i]);
        }
        else
        {
            break;
        }

        /*FAZER A LOGICA PARA IMPRIMIR O ARQUIVO PELO PAGE UP E PAGE DOWN*/


    }

    /*Loop para pegar os eventos do teclado, no caso os caracteres imprimiveis para serem colocado no arquivo*/
    do
    {
        /*Pega uma a??o do teclado*/
        if(hit(KEYBOARD_HIT))
        {
            /*Pega o evento de origem do teclado*/
            evento_para_escrita = Evento();

            /*Verifica se ? um evento do teclado*/
            if(evento_para_escrita.tipo_evento & KEY_EVENT)
            {
                /*tecla pressionada ou n?o */
                if(evento_para_escrita.teclado.status_tecla == LIBERADA)
                {
                    /*Verifica??o para impress?o de caracteres que s?o imprimiveis na tela e para que n?o imprima as setas de dire??o ao mover o cursor sobre o arquivo*/
                    if((evento_para_escrita.teclado.key_code > 45 && evento_para_escrita.teclado.key_code <= 254) || evento_para_escrita.teclado.key_code == ' ')
                    {
                        /*Pega-se o c?digo da tecla correspondente pressionada em ascii e imprime na tela, ? necess?rio pegar novamente a tecla, pois caso n?o haja essa linha,
                        as teclas pegas apenas ser?o em maiusculas, nao em minusculas*/
                        evento_para_escrita.teclado.ascii_code = evento_para_escrita.teclado.ascii_code;

                        /*Verifica qual modo o usuario esta, caso entre na verifica??o esta no modo de sobrescrita de caracteres*/
                        if(string->modo)
                        {
                            /*Quando coloco um caractere, a posi??o onde estou andando com o cursor na linha deve andar tambem*/
                            move_cursor_na_coluna += 1;
                            string->matriz_de_linhas[move_cursor_na_linha][move_cursor_na_coluna] = evento_para_escrita.teclado.ascii_code;
                            
                            /*Imprime o c?digo da tecla correspondente dentro do intervalo especificado na condi??o*/
                            putchar(evento_para_escrita.teclado.ascii_code);
                        }
                        /*Modo de inser??o de caracteres
                        else
                        {   
                            Pega o tamanho da linha atual onde estou
                            tamanho = strlen(string->matriz_de_linhas[move_cursor_na_linha]);

                            Desloca todos os caracteres a direita da posi??o atual do cursor
                            memmove(string->matriz_de_linhas[move_cursor_na_coluna] + move_cursor_na_coluna + 1, string->matriz_de_linhas[move_cursor_na_linha] + move_cursor_na_coluna, tamanho - move_cursor_na_coluna + 1);
                            string->matriz_de_linhas[move_cursor_na_linha][move_cursor_na_coluna] = evento_para_escrita.teclado.ascii_code;
                        }*/
                    }
                    


                    /*Casos para cada tecla*/
                    switch(evento_para_escrita.teclado.key_code)
                    {
                        /*Navega??o no arquivo usando o cursor*/
                        case SETA_PARA_DIREITA:
                        {
                            /*Verifica??o para n?o ultrapassar o fim da linha, ao estar dentro do intervalo ? incrementado o cursor, o '\0' ? justamente para o fim da ultima linha, ja que ela nao contem '\n'*/
                            if(string->matriz_de_linhas[move_cursor_na_linha][move_cursor_na_coluna] != '\n' && string->matriz_de_linhas[move_cursor_na_linha][move_cursor_na_coluna] != '\0')
                            {
                                /*Posiciona o cursor*/
                                move_cursor_na_coluna += 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_na_coluna, string->posicao_cursor_escrita.Y + LARGURA/ALTURA + move_cursor_na_linha);
                                
                            }
                            break;
                        }

                        case SETA_PARA_ESQUERDA:
                        {
                            /*Verifica??o para a movimenta??o do cursor n?o ser menor do que o inicio da coordenada do meu arquivo*/
                            if(move_cursor_na_coluna >= string->posicao_cursor_escrita.X)
                            {
                                /*Posiciona o meu cursor quando ando para atr?s*/
                                move_cursor_na_coluna -= 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_na_coluna, string->posicao_cursor_escrita.Y + LARGURA/ALTURA + move_cursor_na_linha);
                            }
                            break;
                        }
                        
                        case SETA_PARA_BAIXO:
                        {
                            
                            /*Verifica o tamanho das linhas do meu arquivo, caso chegue na linha final n?o consigo ultrapassa-la*/
                            if(move_cursor_na_linha < string->index_linha_matriz)
                            {
                                /*A linha zera para que eu possa andar pelas linhas at? o '\n' dela*/
                                move_cursor_na_linha += 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_na_coluna, string->posicao_cursor_escrita.Y + LARGURA/ALTURA + move_cursor_na_linha);   
                            }
                            
                            break;
                        }

                        case SETA_PARA_CIMA:
                        {
                            /*Ao subir com o cursor nao pode ultrapassar a 1? linha*/
                            if(move_cursor_na_linha >= string->posicao_cursor_escrita.X)
                            {
                                move_cursor_na_linha -= 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_na_coluna, string->posicao_cursor_escrita.Y + LARGURA/ALTURA + move_cursor_na_linha);
                            }
                    
                            break;
                        }

                        /*Sobrescreve caracteres*/
                        case INSERT:
                        {
                            /*Quando queira sobrescrever os caracteres troca de modo*/
                            string->modo = 1;
                            break;
                        }
                        
                        /*Volta apagando um caractere*/
                        case BACKSPACE:
                        {
                            /*Verifica se posso decrementar a linha*/
                            if(move_cursor_na_coluna >= 0)
                            {
                                /*move o cursor*/
                                move_cursor_na_coluna -= 1;
                                gotoxy(string->posicao_cursor_escrita.X + move_cursor_na_coluna, string->posicao_cursor_escrita.Y + LARGURA/ALTURA + move_cursor_na_linha);

                                /*Referente ao espa?o em branco na tabela ascii, usando pucthar ao inv?s do printf por causa do \n no final*/
                                putchar(32);
                            }
                            break;
                        }

                        /*Sai do loop*/
                        case ESC:
                        {
                            /*Zera as 2 variaves de controle do cursor e sai do loop por meio da variavel 'esc_pressionado'*/
                            move_cursor_na_coluna = 0;
                            move_cursor_na_linha = 0;
                            esc_pressionado = 0;
                            break;
                        }

                        /*Vai para o final do arquivo, ?ltima linha*/
                        case PAGE_DOWN:
                        {
                            /*Pega o tamanho da ultima linha do arquivo*/
                            ultima_linha = strlen(string->matriz_de_linhas[string->index_linha_matriz]);
                            move_cursor_na_coluna = ultima_linha;
                            move_cursor_na_linha = string->index_linha_matriz;

                            /*Posiciona o cursor na ultima linha do arquivo*/
                            gotoxy(move_cursor_na_coluna, move_cursor_na_linha);
                            break;
                        }

                        /*Vai para o inicio do arquivo, 1? linha*/
                        case PAGE_UP:
                        {
                            move_cursor_na_coluna = 1;
                            move_cursor_na_linha = 1;

                            /*Posiciona meu cursor no inicio do arquivo*/
                            gotoxy(move_cursor_na_coluna, move_cursor_na_linha);
                            break;
                        }

                        /*Volta no inicio da linha da string*/
                        case HOME:
                        {
                            move_cursor_na_coluna = 1;

                            /*Posiciona no inicio da linha que esta meu cursor*/
                            gotoxy(move_cursor_na_coluna, move_cursor_na_linha + 1);
                            break;
                        }
                        
                        /*Vai pro final da linha aonde o cursor esta*/
                        case END:
                        {
                            cursor_final_linha = strlen(string->matriz_de_linhas[move_cursor_na_linha]);
                            move_cursor_na_coluna = cursor_final_linha;
                            /*Posiciona o cursor*/
                            gotoxy(move_cursor_na_coluna, move_cursor_na_linha + 1);
                            break;
                        }
                    }
                }
            }
        }

    /*Loop at? o ESC ser pressionado*/
    }while(esc_pressionado);
    
}

/*Fun??o que imprime as op??es de menu na tela*/
void Imprime_op_Menu(TAM_JANELA *janela, STRINGS *string, USUARIO *op, char *letras)
{
    int i;

    /*Armazenar? o tamanho de cada string*/
    int tam_opcao_menu = 0;

    /*Armazenar? a posi??o da letra de atalho encontrada nas op??es de menu*/
    int pos;

    /*Armazenar? um ponteiro para a posi??o da letra encontrada nas strings*/
    char *p_posicao_letra;

    /*Armazenar? a coordenada de onde devo destacar a tecla de atalho*/
    COORD Ponto_destaque;

    /*Imprime na tela as op??es do menu*/
    for(i = 0; i < QTD_STRING; i++)
    {   
        /*Seta o lugar aonde deve ser impresso o menu*/
        gotoxy(janela->coordenadas_janela.X + tam_opcao_menu + 1, janela->coordenadas_janela.Y + LARGURA/ALTURA/2);

        /*Foi criada outro tipo COORD para representar a coordenada do destaque da letra de atalho, poderia utilizar-se somente a coordenada atual da janela.
        Mas o c?digo ficaria um pouco confuso*/
        Ponto_destaque.X = wherex();
        Ponto_destaque.Y = wherey();


        /*Verifica??o da navega??o do usuario por meio das teclas direcionais*/
        if(i == op->escolha_do_usuario)
        {
            /*Quando uma op??o for selecionada, eu tenho a coordenada dela para imprimir o submenu dessa op??o, caso precise*/
            op->coordenadas_submenus.X = wherex();
            op->coordenadas_submenus.Y = wherey();

            /*Cor para somente simular uma navega??o entre as op??es*/
            textcolor(YELLOW);
        }

        /*Imprime a string referente a op??o do menu*/
        printf("%s", string->menu[i]);
        
        /*Colore a letra quando apertado o 'ALT_ESQUERDO'*/
        if(op->controle_do_alt)
        {
            /*A fun??o strchr retorna um ponteiro com a posi??o da 1? ocorr?ncia da letra dentro de uma string.*/
            p_posicao_letra = strchr(string->menu[i], letras[i]);

            /*? feito um calculo para pegar a posi??o inteira da letra na string*/
            pos = p_posicao_letra - string->menu[i];

            /*Com a posi??o da letra encontrada em m?os, esta ? somada com a coordenada atual*/
            gotoxy(Ponto_destaque.X + pos, Ponto_destaque.Y);

            /*Modifica a cor do texto para demostrar o destaque da letra de atalho*/
            textcolor(op->cor_atalho);
            printf("%c", letras[i]);
           
        }
        
        /*Ap?s imprimir na tela a op??o com a cor de navega??o padrao do menu, volta-se a cor original do prompt pra nao colorir toda a tela*/
        textcolor(string->cores_texto);

        /*Como o Ponto_destaque, que ? uma coordenada para pintar a letra ao pressionamento do ALT, j? esta pegando a coordenada atual da minha string,
        reuso ela para simplesmente armazenar em um vetor de coordenadas, as coordenadas de todas as strings, para reusar na funcionalidade dos atalhos*/
        string->vetor_cord_menu[i] = Ponto_destaque;

        /*O tamanho da opcao armazena o tamanho da string do menu e o soma com a quantidade de espa?amento declarado fixo,
        isso faz com que haja um espa?amento entre as op??es do menu independente do tamanho da string */
        tam_opcao_menu += strlen(string->menu[i]) + ESPACAMENTO;

    }
}

/*Fun??o para inicializar as variaveis*/
void Inicializacao_Variaveis(STRINGS *string, USUARIO *op, TAM_JANELA *janela)
{
    /*Declara??o da op??o do usu?rio*/
    op->escolha_do_usuario = 0;

    /*Controle do alt*/
    op->controle_do_alt = 0;

    /*Controla o desenho da janela, para que eu consiga mover o cursor,
    ? inicializado com 1 pois preciso que imprima na tela pela 1? vez a janela*/
    op->controla_evento = 1;

    /*Variavel para saida do loop principal da main*/
    op->esc_apertado = 1;

    /*Precisa imprimir ao menos 1 vez*/
    op->imprime_janela_cor_diferente = 1;

    /*Coordenadas da Janela, x e y, para eu poder imprimi-la na tela*/
    janela->coordenadas_janela.X = 1;
    janela->coordenadas_janela.Y = 1;

    /*Come?a com a inser??o de caracteres*/
    string->modo = 0;

    /*Inicializa??o da quantidade de linhas no arquivo*/
    string->index_linha_matriz = 0;

    /*Atribui o tamanho da janela do console*/
    string->limite_maximo_Janela = tamanhoJanelaConsole();

    /*Aloco memoria para a tela de salvamento de acordo com o tamanho maximo da minha janela*/
    string->Tela = (char *)malloc(string->limite_maximo_Janela.X * string->limite_maximo_Janela.Y * 2 * sizeof(char));

}

/*Fun??o que le o teclado do usuario*/
void Le_Teclado(LE_TECLADO *leitura, USUARIO *op, STRINGS * string)
{
    /*UMA IDEIA ? COLOCAR O TEXTO IMPRESSO EMBAIXO DO MENU, ASSIM CONSIGO TER A LOCALIZA??O DA ONDE VAI SER IMPRESSO E COMO FAZER,
    A IDEIA ? IMPRIMIR POR BLOCOS, CADA BLOCO EU IMPRIMO O TEXTO AP?S PASSAR O LIMITE DE CADA BLOCO, POSSO GUARDAR A TELA ANTERIOR E COLOCAR NA TELA
    */

    /*Pego a tela atual para salvamento*/
    _gettext(1, 1, string->limite_maximo_Janela.X, string->limite_maximo_Janela.Y, string->Tela);

    /*Identifica um 'hit' do teclado*/   
    if(hit(KEYBOARD_HIT))
    {
        /*Atribui??o do evento que ocorreu*/
        leitura->tecla = Evento();
        
        /*Verifica??o caso seja um evento origin?rio do teclado*/
        if(leitura->tecla.tipo_evento & KEY_EVENT)
        {
            /*Precisa ser aqui dentro o controle dos eventos, pois somente se for um evento do teclado, vai ser retornado se vai ou nao ser impresso o menu*/
            op->controla_evento = Mapeia_teclas_Entrada(leitura);

            if(op->controla_evento)
            {
                /*Verifica??o da tecla se foi liberada ao pressionada*/
                if(leitura->tecla.teclado.status_tecla == LIBERADA)
                {
                    
                    /*gotoxy(1, LARGURA/ALTURA + 1);
                    printf("asdasd");*/   
                    /*O controle da tecla alt esquerda ? atribuida em 0 pois a tecla esta solta*/
                    op->controle_do_alt = 0;

                    /*Casos para o menu*/
                    switch(leitura->tecla.teclado.key_code)
                    {
                        
                        /*Seleciona a op??o do menu principal*/
                        case ENTER:
                        {

                            /*De acordo com a escolha do usuario, uma das op??es sera selecionada*/
                            switch(op->escolha_do_usuario)
                            {
                                /*Caso quando o usuario escolher o submenu arquivo*/
                                case 0:
                                {
                                    /*Chama fun??o para abrir o submenu arquivo*/
                                    Submenu_Arquivo(string);

                                    /*Ap?s ter chamado minha fun??o coloco a tela que foi salva anteriormente e o mesmo ? feito para as demais fun??es
                                    puttext(1, 1, string->limite_maximo_Janela.X, string->limite_maximo_Janela.Y, string->Tela);*/
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

                                    /*Chama a fun??o para pegar o numero dado pelo usuario*/
                                    Caractere_X(leitura, op, string);
                                    puttext(1, 1, string->limite_maximo_Janela.X, string->limite_maximo_Janela.Y, string->Tela);
                                    break;
                                }

                                /*Caso para trocar a cor de fundo*/
                                case 3:
                                {
                                    /*Chama a fun??o para o submenu de cor de fundo*/
                                    Submenu_background(string, op);
                                    puttext(1, 1, string->limite_maximo_Janela.X, string->limite_maximo_Janela.Y, string->Tela);
                                    break;
                                }

                                /*Caso para trocar a cor de texto*/
                                case 4:
                                {
                                    /*Chama a fun??o para o submenu de cor de texto*/
                                    Submenu_cor_texto(string, op);
                                    puttext(1, 1, string->limite_maximo_Janela.X, string->limite_maximo_Janela.Y, string->Tela);
                                    break;
                                }
                            }

                        }

                        /*Navega??o ? direita*/
                        case SETA_PARA_DIREITA:
                        {
                            
                            /*Foi criado uma variavel para a escolha do usuario para simular a navega??o do menu, ? necessario somente
                            modificar o valor da pr?pria variavel conforme o usuario aperta as teclas direcionais, a verifica??o ? feita para a navega??o
                            ficar limitada entre o intervalo da 1? a ultima op??o, o mesmo ? feito nas outras setas de dire??o, porem com verifica??es distintas*/
                            if(op->escolha_do_usuario >= 0 && op->escolha_do_usuario < QTD_STRING - 1)
                            {
                                op->escolha_do_usuario += 1;
                            }
                            break;
                        }

                        /*Navega??o ? esquerda*/
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
                        /*? definido o alt_esquerdo como 1 pois esta sendo pressionado, a cor muda para azul*/
                        op->controle_do_alt = 1;
                        op->cor_atalho = BLUE;

                        /*switch para a outra tecla ap?s o ALT_ESQUERDO*/
                        switch(leitura->tecla.teclado.key_code)
                        {
                            /*Os gotoxy() s?o para setar a coordenada correspondente ao lugar aonde ser? impresso o submenu de cada op??o do menu principal*/
                            /*Teclas de atalho para chamada das op??es do menu principal*/
                            /*Atalho para op??o 'ARQUIVO'*/
                            case 'A':
                            {

                                /*Chama a fun??o para a abertura do arquivo*/
                                Submenu_Arquivo(string);
                                break;
                            }
                            
                            /*Atalho para op??o 'ALINHAMENTO'*/
                            case 'L':
                            {
                                break;
                            }

                            /*Atalho para op??o 'ALTERAR X'*/
                            case 'X':
                            {

                                /*Chama a fun??o para o caractere TAB*/
                                Caractere_X(leitura, op, string);
                                break;
                            }

                            /*Atalho para op??o 'COR FUNDO'*/
                            case 'F':
                            {

                                /*Chamada da fun??o para trocar a cor de fundo*/
                                Submenu_background(string, op);
                                break;
                            }

                            /*Atalho para op??o 'COR TEXTO'*/
                            case 'T':
                            {

                                /*Chamada para a fun??o que troca a cor de texto*/
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
    



/*Controla as teclas que ser?o pressionadas pelo teclado, para imprimir novamente a janela de menu ? necessario mapear as teclas*/
int Mapeia_teclas_Entrada(LE_TECLADO *leitura)
{
    /*Mapeamento de cada tecla*/

    /*Verifica??o do alt esquerdo pois ? uma tecla de controle*/
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

/*Fun??o que as modifica??es feitas no arquivo que foi aberto*/
void Salvar_Arquivo(STRINGS *string)
{
    int i;
    FILE *escrita;

    /*Encerra o arquivo aberto*/
    fclose(string->arquivo_origem);

    /*Abre pra escrever*/
    escrita = fopen(string->arquivo_txt, "w");

    /*Escreve tudo no meu arquivo*/
    for(i = 0; i < string->index_linha_matriz; i++)
    {
        fprintf(escrita, "%s", string->matriz_de_linhas[i]);
    }   

    /*Fecha o arquivo de escrita*/
    fclose(escrita);

    /*Libera 1? a memoria alocada para as linhas*/  
    for(i = 0; i < string->index_linha_matriz; i++)
    {
        free(string->matriz_de_linhas[i]);
    }

    /*Limpa a memoria que foi alocada para a matriz*/
    free(string->matriz_de_linhas);  

    printf("Arquivo Salvo com sucesso!");
}   

/*Fun??o para apresentar o submenu quando for apertado na op??o arquivo*/
void Submenu_Arquivo(STRINGS *string)
{
    /*? criado outro tipo EVENTO para armazenar as teclas da navega??o e escolha do submenu arquivo*/
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
            /*Imprime as op??es de arquivo*/
            for(i = 0; i <= 1; i++)
            {
                if(i == escolha_setas_submenu)
                {
                    textcolor(YELLOW);
                }

                /*Como j? tenho a posi??o de cada string do menu, pode ser feito manualmente acessando seu ?ndice*/
                gotoxy(string->vetor_cord_menu[0].X, string->vetor_cord_menu[0].Y + i + 1);
                printf("%s", string->submenu_arquivo[i]);
                textcolor(string->cores_texto);

            }    
            /*S? ? necessario imprimir uma 1? vez, caso o usuario pressione as teclas de navega??o, ai a variavel volta com seu valor 1, caso nao continua zerado*/
            controla_sub = 0;
        }
        
        /*Armazena os eventos do teclado*/
        sub_arquivo = Evento();

        /*Verifica se ? um evento do teclado*/
        if(sub_arquivo.tipo_evento & KEY_EVENT)
        {   
            /*Verifica se foi liberada a tecla*/
            if(sub_arquivo.teclado.status_tecla == LIBERADA)
            {
                /*Qual tecla foi apertada*/
                switch(sub_arquivo.teclado.key_code)
                {
                    /*Navega??o do submenu arquivo*/
                    case SETA_PARA_BAIXO:
                    {
                        /*Navega??o do submenu na op??o arquivo*/
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

                    /*Meio de saida do loop e entrada em outra fun??o*/
                    case ENTER:
                    {
                        /*Ao apertar o enter, ? aonde a posi??o 'escolha_estas_submenu' vai estar, entao eu tenho controle de qual op??o sera selecionada somente
                        com uma variavel*/
                        switch(escolha_setas_submenu)
                        {

                            /*Usuario optou por abrir um arquivo*/
                            case 0:
                            {
                                /*Chama a fun??o para abrir o arquivo*/
                                Abre_Arquivo(string);
                                saida = 0;
                                controla_sub = 0;
                                break;
                            }

                            /*Usuario optou pra salvar o arquivo aberto*/
                            case 1:
                            {
                                /*Chama a fun??o para salvar o arquivo*/
                                Salvar_Arquivo(string);
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

/*Fun??o para imprimir os submenus da op??o 'COR FUNDO'*/
void Submenu_background(STRINGS *string, USUARIO *op)
{
    EVENTO sub_cor_fundo;
    int i = 0;
    int saida = 1;
    int controla_sub_cor = 1;
    int escolhas_setas_background = 0;
    
    /*Pega os eventos do teclado para navegar entre as op??es do menu*/
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

                /*Mesma funcionalidade da fun??o Submenu_arquivo*/
                gotoxy(string->vetor_cord_menu[3].X ,string->vetor_cord_menu[3].Y + i + 1);
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
                    /*Navega??o no menu cores de fundo*/
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

                /*Seta a coordenada correta dpara impress?o do meu submenu*/
                gotoxy(string->vetor_cord_menu[4].X, string->vetor_cord_menu[4].Y + i + 1);
                printf("%s", string->submenu_cores[i]);
                textcolor(string->cores_texto);
            }
            controla_sub_cor_texto = 0;
        }

        /*Pega os eventos da teclado*/
        cor_texto = Evento();
        if(cor_texto.tipo_evento & KEY_EVENT)
        {
            /*verifica a libera??o da tecla*/
            if(cor_texto.teclado.status_tecla == LIBERADA)
            {
                switch(cor_texto.teclado.key_code)
                {
                    /*Navega??o do submenu de troca de cor do texto*/
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

                    /*Escolheu cor*/
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
    