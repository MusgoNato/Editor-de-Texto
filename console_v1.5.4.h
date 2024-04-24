/* Biblioteca que permite ler diferentes fontes de entrada: teclado e mouse.

   OBSERVA��O: para identificar as os pressionamentos dos bot�es do mouse � preciso que a op��o 
			   "Modo de Edi��o R�pida" (aba "Op��es" das propriedades do janela do Console de ocmando)
			   esteja DESMARCADA (unchecked).
*/
#ifndef _CONSOLE
#define _CONSOLE

#include <windows.h>
/* -> Estrutura COORD:
      typedef struct _COORD{
              SHORT X;   -> inteiro curto
              SHORT Y;   -> inteiro curto
              } COORD;
   -> Tipos WORD, DWORD e LPSTR
*/

/****************************************************************************************************************/
/*                                  IN�CIO DAS DECLARA��ES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/
#define F1 112
#define F2 113
#define F3 114
#define F4 115
#define F5 116
#define F6 117
#define F7 118
#define F8 119
#define F9 120
#define F10 121
#define F11 122
#define F12 123

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define ESPACO 32
#define TAB 9

/* Enhanced keys */
#define INSERT 45
#define DEL 46
#define PAGE_UP 33
#define PAGE_DOWN 34
#define END 35
#define HOME 36
#define SETA_PARA_ESQUERDA 37
#define SETA_PARA_CIMA 38
#define SETA_PARA_DIREITA 39
#define SETA_PARA_BAIXO 40

/* Teclas de status */
#define SHIFT_ESQUERDO_PRESSIONADO 0x0200  /* (constante definida por mim = 0x200 = shift esquerdo pressionado) + (0x010 = shift pressionado) = 0x210. Valor definido com base em uma extens�o dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
#define SHIFT_DIREITO_PRESSIONADO 0x0400  /* (constante definida por mim = 0x400 = shift direito pressionado) + (0x010 = shift pressionado) = 0x410. Valor definido com base em uma extens�o dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */


/* constantes definidas para identificar a libera��o de um determinado bot�o do mouse */
#define FROM_LEFT_1ST_BUTTON_RELEASED FROM_LEFT_1ST_BUTTON_PRESSED
#define FROM_LEFT_2ND_BUTTON_RELEASED FROM_LEFT_2ND_BUTTON_PRESSED
#define FROM_LEFT_3RD_BUTTON_RELEASED FROM_LEFT_3RD_BUTTON_PRESSED
#define FROM_LEFT_4TH_BUTTON_RELEASED FROM_LEFT_4TH_BUTTON_PRESSED
#define RIGHTMOST_BUTTON_RELEASED RIGHTMOST_BUTTON_PRESSED

/* dar a op��o ao programador de usar constantes em portugu�s, caso queira */
#define BOTAO_ESQUERDO_PRESSIONADO FROM_LEFT_1ST_BUTTON_PRESSED
#define BOTAO_ESQUERDO_LIBERADO FROM_LEFT_1ST_BUTTON_RELEASED
#define BOTAO_DIREITO_PRESSIONADO RIGHTMOST_BUTTON_RELEASED
#define BOTAO_DIREITO_LIBERADO RIGHTMOST_BUTTON_RELEASED

/* constantes utilizadas pela fun��o IdentificarEvento() para definir o nivel
   de detalhamento das informa��es a serem coletadas de um evento */
#define MINIMO 1
#define MAXIMO 2

#define BIT_SHORT_MAIS_SIGNIFICATIVO 0x80  /* (0x80) na base hexadecimal = (128) na base 10 = (1000 0000) na base 2 */
#define TECLA_PRESSIONADA 0x80
/****************************************************************************************************************/
/*                                  FIM DAS DECLARA��ES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/




/****************************************************************************************************************/
/*                                   DECLARA��ES DE ESTRUTURAS E ENUMERA��ES                                    */
/****************************************************************************************************************/

 /* estrutura para o armazenamento das cores da janela de console */
    typedef struct{
                  int CorTexto;      /* cor do texto da janela de prompt atual */
		          int CorFundo;      /* cor de fundo da janela de prompt atual */
                  }CORES;


 /* tipo STATUS contendo os valores para ligar e desligar o cursor do mouse da tela */
    typedef enum{DESLIGAR, LIGAR} STATUS;


 /* tipo VISIBILIDADE */
    typedef enum{INVISIVEL, VISIVEL} VISIBILIDADE;


 /* tipo que permite identificar que tipo de evento deve ser verificada a exist�ncia no buffer de eventos */
    typedef enum{KEYBOARD_HIT, MOUSE_HIT, ALL} TYPE_HIT;


 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
    enum T_STATUS_TECLA{LIBERADA, PRESSIONADA};
    typedef struct T_TECLADO{
                            enum T_STATUS_TECLA status_tecla; /* LIBERADA ou PRESSIONADA */
		 				    DWORD codigo_tecla; /* c�digo num�rico que identifica uma tecla independente do tipo do teclado */
                            DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de dire��o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
								 						   SHIFT_PRESSED */
                            } TECLADO;

 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684239%28v=vs.85%29.aspx */
    typedef struct T_MOUSE{
                          DWORD botao_pressionado; /* FROM_LEFT_1ST_BUTTON_PRESSED, FROM_LEFT_2ND_BUTTON_PRESSED, FROM_LEFT_3RD_BUTTON_PRESSED,
                                                      FROM_LEFT_4TH_BUTTON_PRESSED, RIGHTMOST_BUTTON_PRESSED */
		 				  DWORD botao_clicou;      /* se o bot�o tiver sido liberado, ap�s ter sido pressionado */
                          COORD posicao; /* coordenadas (em forma de c�lulas de caracteres e n�o de pixels) do cursor do
						                    mouse em termos do tamanho (em linhas e colunas) do buffer
							 			    de console que estiver definido para a janela */
                          DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de dire��o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
							 							   SHIFT_PRESSED */
						  DWORD flags_qual_evento_mouse; /* DOUBLE_CLICK, MOUSE_HWHEELED, MOUSE_MOVED, MOUSE_WHEELED */
                          } MOUSE;

 /* Evento que pode ter acontecido e que � identificado pela fun��o Evento() */
    typedef struct T_EVENTO{
                           WORD tipo_evento; /* pode ser MOUSE_EVENT ou KEY_EVENT */
		  				   TECLADO teclado; /* caso tenha ocorrido um KEY_EVENT, ent�o esta estrutura ser� prenchida
						                    com os dados correspondentes */
						   MOUSE mouse;    /* caso tenha ocorrido um MOUSE_EVENT, ent�o esta estrutura ser� prenchida
						                    com os dados correspondentes */
                           }EVENTO;


/****************************************************************************************************************/
/*                                  FIM DAS DECLARA��ES DE ESTRUTURAS E ENUMERA��ES                             */
/****************************************************************************************************************/





/****************************************************************************************************************/
/*                                IN�CIO DAS DECLARA��ES DOS PROT�TIPOS DAS FUN��ES                             */
/****************************************************************************************************************/

 /*****************************************************************************************************************
  Descri��o: imprime a mensagem do tipo LPSTR (ponteiro para uma string) juntamente com o c�digo do �ltimo erro
             ocorrido no programa obtido do fluxo de erro (stderr) e encerra o programa.
  Par�metros de entrada:
   -> Vari�vel do tipo LPSTR: uma mensagem a ser impressa na tela.
  Retorno da fun��o:
   -> Nenhum.
 *****************************************************************************************************************/
 void ErrorExit (LPSTR);




 /*****************************************************************************************************************
  Descri��o: permitir e identificar com todos os detalhes, eventos origin�rios do teclado e/ou do mouse.
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura EVENTO:
      - Campo "tipo_evento" que � do tipo WORD (inteiro sem sinal de 2 bytes):
	      -> Valor MOUSE_EVENT: significa que o evento lido do buffer da janela de console � um evento origin�rio do
		                       MOUSE;
		  -> Valor KEY_EVENT: significa que o evento lido do buffer da janela de console � um evento origin�rio do
		                     TECLADO;
		  -> Observa��o 1: esta fun��o descarta os eventos FOCUS_EVENT, MENU_EVENT e WINDOW_BUFFER_SIZE_EVENT.
		                   Caso a identifica��o de algum desses eventos seja necess�rio, a fun��o deve ser
			 			   estendida para que armazene neste campo o valor correspondente a um desses 3 eventos;
          -> Observa��o 2: o campo "tipo_evento" � um campo de bits. Isto �, cada um dos valores indicados
		                   est� associado a um bit do campo. Portanto, a identifica��o de qual valor est� armazenado
                           no campo deve ser feito por meio dos operadores bit-a-bit.
						   Exemplo: EVENTO e;
						            e = Evento();
						            if (e.tipo_evento & MOUSE_EVENT) printf("Foi gerado um evento pelo mouse");
						            if (e.tipo_evento & KEY_EVENT) printf("Foi gerado um evento pelo teclado");
	  - Campo "teclado" que � uma estrutura do tipo TECLADO: se o campo "tipo_evento" contiver um valor KEY_EVENT
	                                                         ent�o esta estrutura conter� todos os dados relativos
															 a esse evento. Caso contr�rio, os valores contidos
															 nesta estrutura n�o tem sentido e, portanto, n�o devem
 															 ser utilizados.
	      -> Campo "status_tecla" do tipo enumera��o: armazena se o evento do teclado foi o pressionamento
		                                              ou a libera��o de uma tecla.
		     - Valor LIBERADA: evento corresponde � libera��o do pressionamento de uma tecla;
			 - Valor PRESSIONADA: evento corresponde ao pressionamento de uma tecla.
		  -> Campo "codigo_tecla" do tipo DWORD: contem um valor inteiro �nico independente do tipo do teclado para
		                                       cada uma das teclas do teclado.
		     - Observa��o:
			   Recomenda-se o uso das constantes definidas no in�cio deste arquivo (#defines) para
			   referenciar as teclas, ao inv�s da escrita no programa do pr�prio c�digo da tecla.
		  -> Campo "status_teclas_controle" do tipo DWORD (4 bytes): contem o status das diversas teclas de
		                                                             controle.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK est� ligada;
             - Valor ENHANCED_KEY: a tecla pressionada � uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIRE��O, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda est� pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda est� pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK est� ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita est� pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita est� pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK est� ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT est�o pressionadas.
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observa��o:
			    Este campo "status_teclas_controle" � um campo de bits. Isto �, cada um dos valores indicados
		        est� associado a um bit do campo. Portanto, a identifica��o de qual valor est� armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
						 if (e.tipo_evento & KEY_EVENT)
						 {
						     if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK est� acessa");
						 }
	  - Campo "mouse" que � uma estrutura do tipo MOUSE:
          -> Campo "botao_pressionado" do tipo DWORD:
             - Valor FROM_LEFT_1ST_BUTTON_PRESSED: primeiro bot�o da esquerda pressionado;
			 - Valor FROM_LEFT_2ND_BUTTON_PRESSED: segundo bot�o da esquerda pressionado;
			 - Valor RIGHTMOST_BUTTON_PRESSED: bot�o mais � direita pressionado.
             -> Observa��o 1:
			    Este campo "botao_pressionado" � um campo de bits. Isto �, cada um dos valores indicados est�
				associado a um bit do campo. Portanto, a identifica��o de qual valor est� armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
						 if (e.tipo_evento & MOUSE_EVENT)
						 {
							 if (e.mouse.botao_pressionado & RIGHTMOST_BUTTON_PRESSED)
								 printf("O bot�o da direita est� pressionado");
						 }
             -> Observa��o 2:
			    Foram definidas, na se��o "DEFINES e CONSTANTES", constantes em portugu�s, para os bot�es esquerdo
                e direito do mouse, que podem ser utilizadas ao inv�s dos valores anteriores para aumentar
				a legibilidade do c�digo:
				- BOTAO_ESQUERDO_PRESSIONADO
                - BOTAO_DIREITO_PRESSIONADO
             -> Observa��o 3:
			    Embora o "windows.h" colete e disponibilize informa��es para mais dois bot�es que porventura o
				mouse tenha (constantes FROM_LEFT_3RD_BUTTON_PRESSED e FROM_LEFT_4TH_BUTTON_PRESSED, correspondentes
				ao terceiro e quarto bot�es da esquerda, respectivamente), esta fun��o ignora esses valores. Portanto,
				caso seja necess�rio essa identifica��o, a fun��o deve ser estendida nesse aspecto.
		  -> Campo "botao_clicou" do tipo DWORD: cont�m se o evento foi a libera��o de algum dos bot�es do mouse
		                                         que previamente estavam pressionados, definindo um clique do mouse.
             - Valor FROM_LEFT_1ST_BUTTON_RELEASED: primeiro bot�o da esquerda foi liberado (clicou);
			 - Valor FROM_LEFT_2ND_BUTTON_RELEASED: segundo bot�o da esquerda foi liberado (clicou);
			 - Valor RIGHTMOST_BUTTON_RELEASED: bot�o mais � direita foi liberado (clicou).
             -> Observa��o 1:
			    Este campo "botao_clicou" � um campo de bits. Isto �, cada um dos valores indicados est�
				associado a um bit do campo. Portanto, a identifica��o de qual valor est� armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
						 if (e.tipo_evento & MOUSE_EVENT)
						 {
						     if (e.mouse.botao_clicou & RIGHTMOST_BUTTON_RELEASED)
						         printf("O bot�o da direita clicou/foi liberado");
						 } 
             -> Observa��o 2:
			    Foram definidas, na se��o "DEFINES e CONSTANTES", constantes em portugu�s, para os bot�es esquerdo
                e direito do mouse, que podem ser utilizadas ao inv�s dos valores anteriores para aumentar
				a legibilidade do c�digo:
				- BOTAO_ESQUERDO_LIBERADO
                - BOTAO_DIREITO_LIBERADO
          -> Campo "posicao" que � uma estrutura do tipo COORD: guarda as coordenadas (x,y) na janela de console em
                                                                que ocorreu o evento do mouse. As coordenadas s�o
																dadas em posi��es de caracteres e n�o de pixels.
			 - Campo X: coluna da janela de console em que ocorreu o evento do mouse;
             - Campo Y: linha da janela de console em que ocorreu o evento do mouse.

		  -> Campo "status_teclas_controle" do tipo DWORD: contem o status das diversas teclas de controle, quando
		                                                   ocorreu o evento do mouse.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK est� ligada;
             - Valor ENHANCED_KEY: a tecla pressionada � uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIRE��O, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda est� pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda est� pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK est� ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita est� pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita est� pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK est� ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT est�o pressionadas;
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observa��o:
			    O campo "status_teclas_controle" � um campo de bits. Isto �, cada um dos valores indicados
		        est� associado a um bit do campo. Portanto, a identifica��o de qual valor est� armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
						 if (e.tipo_evento & MOUSE_EVENT)
						 {
						     if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK est� acessa");
						 }
		  -> Campo "flags_qual_evento_mouse" do tipo DWORD: identifica qual o tipo de evento do mouse que ocorreu.
             - Valor DOUBLE_CLICK: o segundo clique (pressionado de bot�o de um duplo-clique ocorreu.
               * Observa��o: o primeiro clique � retornado como um evento normal de pressionamento de bot�o.
             - Valor MOUSE_HWHEELED:  a roda de rolagem horizontal do mouse foi girada.
			   * Observa��o: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, ent�o a roda foi
			                 girada para a direita. Caso contr�rio, a roda foi girada para a esquerda.
			                 Exemplo de identifica��o: EVENTO e;
                                                       e = Evento();
													   if (e.tipo_evento & MOUSE_EVENT)
													   {
													       if ( (int)e.mouse.botao_pressionado > 0)
                                                                printf("A roda do mouse foi girada para a direita");
                                                           else
                                                                printf("A roda do mouse foi girada para a esquerda");
													   }
             - Valor MOUSE_MOVED: ocorreu uma mudan�a na posi��o do mouse;
             - Valor MOUSE_WHEELED: a roda de rolagem vertical do mouse foi girada.
			   * Observa��o: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, ent�o a roda foi
			                 girada para a frente. Caso contr�rio, a roda foi girada para tr�s.
			                 Exemplo de identifica��o: EVENTO e;
                                                       e = Evento();
													   if (e.tipo_evento & MOUSE_EVENT)
													   {
                                                           if( (int)e.mouse.botao_pressionado > 0)
                                                               printf("A roda do mouse foi girada para frente");
                                                           else
                                                               printf("A roda do mouse foi girada para tr�s");
													    }
  Observa��es:
   a) Deve ser dada prefer�ncia ao uso desta fun��o ao inv�s da fun��o getch();
   b) Ver a declara��o da estrutura EVENTO na se��o anterior denominada "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
   c) Ver a declara��o da estrutura COORD na se��o anterior denominada "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
   d) Ver a declara��o da estrutura TECLADO na se��o anterior denominada "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES";
   e) Ver a declara��o da estrutura MOUSE na se��o anterior denominada"DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
   f) O tipo WORD � um inteiro sem sinal longo de 2 bytes definido na "windows.h";
   g) O tipo DWORD � um inteiro sem sinal longo de 4 bytes definido na "windows.h";
   h) Os tipos comuns definidos na "windows.h" podem ser consultados em:
      http://msdn.microsoft.com/en-us/library/cc230309.aspx
 *****************************************************************************************************************/
 EVENTO Evento(void);





/*****************************************************************************************************************
  Descri��o: obter as cores de fundo e do texto definidas para a janela de console
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura CORES:
      - Campo CorTexto: cor definida para a escrita de na janela de console.
	  - Campo CorFundo: cor definida para o fundo de qualquer caracteres escrito na
	                    janela de console

  Observa��o:
   -> Ver a declara��o da estrutura CORES na se��o anterior denominada
      "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
 *****************************************************************************************************************/
 CORES getCoresJanela(void);




 /*****************************************************************************************************************
  Descri��o: obter as coordenadas atuais da janela de console na tela.
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console

  Observa��es:
   a) A estrutura COORD � inclu�da por meio do arquivo cabe�alho "windows.h". Contudo, a sua declara��o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que � inclu�do o arquivo
	  cabe�alho "windows.h".
   b) Em outras palavras, retorna as coodenadas (x,y) do pixel do canto superior
      esquerdo da janela de console.
 *****************************************************************************************************************/
 COORD getPosicaoJanela(void);
 


 
 /*****************************************************************************************************************
  Descri��o: obter a resolu��o do monitor em pixels:
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura COORD:
      - Campo X representa o n�mero de pixels da largura
      - Campo Y representa o n�mero de pixels da altura

  Observa��o:
   -> A estrutura COORD � inclu�da por meio do arquivo cabe�alho "windows.h". Contudo, a sua declara��o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que � inclu�do o arquivo
	  cabe�alho "windows.h".
   -> Retornar�  a resolu��o exata configurada para a tela se a escala da fonte estiver definida para 100%. Caso 
      esteja configurada para uma outra escala o valor retornado ser� ajustado com base na escala definida. 
	  Por exemplo: resolu��o da tela seja 1920 x 1080 configurada para 125%. Logo, a fun��o retornar� 1536 x 864 
	               (1980 = 1536 x 1,25  e 1080 = 864 x 1,25),
	  
 *****************************************************************************************************************/
 COORD getResolucaoMonitor(void);




 /*****************************************************************************************************************
  Descri��o: obter, em n�mero de pixels, as dimens�es horizontal e vertical da fonte da janela do console.
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura COORD:
      - Campo X representa a quantidade de pixels na horizontal ocupada por um caractere na janela do console.
      - Campo Y representa a quantidade de pixels na vertical ocupada por um caractere na janela do console.

  Observa��o:
   -> A estrutura COORD � inclu�da por meio do arquivo cabe�alho "windows.h". Contudo, a sua declara��o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que � inclu�do o arquivo
	  cabe�alho "windows.h".
 *****************************************************************************************************************/
 COORD getTamanhoFonteConsole(void);




 /*****************************************************************************************************************
  Descri��o: obter o t�tulo da janela de console.
  Par�metros de entrada:
   -> Nenhum.
   Retorno da fun��o:
   -> Um ponteiro ponteiro para o endere�o da string contendo o t�tulo da janela, ou NULL se a janela
      n�o tiver um t�tulo
 *****************************************************************************************************************/
 char *getTituloConsole(void);




 /*****************************************************************************************************************
  Descri��o: obter se h� algum evento (teclado, mouse, ou redimensionamento da janela) no buffer de eventos
             da janela de console.
  Par�metros de entrada:
   -> Enumera��o TYPE_HIT:
      - Valor KEYBOARD_HIT: identificar somente os eventos origin�rios do teclado;
	  - Valor MOUSE_HIT: identificar somente os eventos origin�rios do mouse;
	  - Valor ALL: identificar qualquer evento presente no buffer de eventos da janela de console, sejam
	               oriundos do teclado, do mouse, ou do redimensionamento da janela.
  Retorno da fun��o:
   -> Um valor inteiro:
      - Valor 0: n�o h� eventos do tipo solicitado no par�metro da fun��o no buffer de eventos da janela de
	             console;
	  - Valor 1: h� um ou mais eventos do tipo solicitado no par�metro da fun��o no buffer de eventos
	             da janela de console.

  Observa��o:
   -> Ver a declara��o da enumera��o TYPE_HIT na se��o anterior denominada
      "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
 *****************************************************************************************************************/
 int hit(TYPE_HIT);




/*****************************************************************************************************************
  Descri��o: apresenta��o detalhada de todas as informa��es poss�veis de serem coletadas sobre um determinado evento
             ocorrido, cuja origem seja, ou o teclado, ou o mouse.
  Par�metros de entrada:
   -> Vari�vel do tipo da estrutura EVENTO:
      - Essa vari�vel deve conter os dados do evento lido anteriormente sobre o qual ser�o coletadas as informa��es;
	  - Ver descri��o do conte�do dos campos da estrutura EVENTO na fun��o Evento();
	  - Exemplo de c�digo: EVENTO e;
	                       e = Evento();
						   IdentificarEvento(e, MAXIMO);
   -> N�mero inteiro que pode ser dois valores:
      - Valor 0: apresentar na tela o m�nimo de informa��es sobre o evento passado como par�metro;
	  - Valor 1: apresentar na tela o m�ximo de informa��es (todas as poss�veis) sobre o evento passado como par�metro;
	  -> Observa��o:
	     Foram definidas duas constantes do tipo DEFINE para este par�metro, em substitui��o ao valores num�ricos 0 e 1.
		 Constantes MINIMO e MAXIMO, correspondente aos valores 0 e 1, respectivamente.
  Retorno da fun��o:
   -> Nenhum.

  Observa��o:
   -> Ver a declara��o da estrutura EVENTO na se��o anterior denominada "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
 *****************************************************************************************************************/
 void IdentificarEvento(EVENTO, int);




 /*****************************************************************************************************************
  Descri��o: obter as dimens�es m�ximas poss�veis de uma janela na resolu��o atual
             do monitor em pixels.
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura COORD:
     - Campo X representa o n�mero de caracteres da largura
     - Campo Y representa o n�mero de caracteres da altura

  Observa��es:
   a) A estrutura COORD � inclu�da por meio do arquivo cabe�alho "windows.h". Contudo, a sua declara��o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que � inclu�do o arquivo
	  cabe�alho "windows.h".
   b) Para poder utilizar esta fun��o � necess�rio fazer uma corre��o no arquivo WINCON.H do gcc.
      Isso porque esta fun��o MaxDimensaoJanela(void) utiliza a fun��o da API do Windows
	  denominada GetCurrentConsoleFont() que somente est� dispon�vel no Windows XP em diante e
 	  por isso o gcc n�o incluiu esse cabe�alho (embora exista sua implementa��o no ".lib" do gcc).
      - CORRE��O A SER FEITA:
	    Caso n�o exista, deve adicionar a seguinte linha no arquivo "wincon.h":
	         BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
	  - ONDE DEVE SER ACRESCENTADA ESSA LINHA NO ARQUIVO "wincon.h":
        1) No arquivo "wincon.h" que est� localizado dentro do diret�rio "include" da sua instala��o do gcc for Windows
	    2) A linha indicada deve ser adicionada dentro do define (caso n�o exista, crie ele)
		     #if (_WIN32_WINNT >= 0x0500)
		          BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
		          ... -> mantenha tudo o que j� existir anteriormente definido dentro do define
		     #endif
 *****************************************************************************************************************/
 COORD MaxDimensaoJanela(void);




 /*****************************************************************************************************************
  Descri��o: ligar ou desligar o cursor piscante na janela de console.
  Par�metros de entrada:
   -> Uma string contendo o novo t�tulo da janela de console.
  Retorno da fun��o:
   -> Enumera��o STATUS:
      - Valor DESLIGAR: desligar o cursor piscante na janela de console;
	  - Valor LIGAR: ligar o cursos piscante na janela de console.

  Observa��o:
   -> Ver a declara��o da enumera��o STATUS na se��o anterior denominada
      "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
 *****************************************************************************************************************/
 void setCursorStatus(STATUS);




 /*****************************************************************************************************************
  Descri��o: fun��o que permite redimensionar a janela de console.
  Par�metros de entrada:
   -> Estrutura COORD:
      - Campo X representa o n�mero de caracteres da nova largura da janela
      - Campo Y representa o n�mero de caracteres da nova altura da janela
  Retorno da fun��o:
   -> Nenhum.

  Observa��o:
   - Recomenda-se que obtenha os valores m�ximos poss�veis para o redimensionamento
     da janela do console por meio de uma chamada � fun��o MaxDimensaoJanela(). Desse
     modo, conseguir� garantir que os valores passados como par�metros para esta fun��o
     n�o ultrapassar� os valores m�ximos poss�veis de redimensionamento da janela do
     console.
 *****************************************************************************************************************/
 void setDimensaoJanela(int largura, int altura);




 /*****************************************************************************************************************
  Descri��o: esconder ou tornar vis�vel a Barra de Tarefas da �rea de trabalho do Windows.
  Par�metros de entrada:
   -> Enumera��o VISIBILIDADE:
      - Valor VISIVEL: tornar vis�vel a Barra de Tarefas;
      - Valor INVISIVEL: esconder a Barra de Tarefas.
  Retorno da fun��o:
   -> Nenhum.

  Observa��o:
   -> Ver a declara��o da enumera��o VISIBILIDADE na se��o anterior denominada
      "DECLARA��ES DE ESTRUTURAS E ENUMERA��ES".
 *****************************************************************************************************************/
 void setEstadoBarraTarefas(VISIBILIDADE);




/*****************************************************************************************************************
  Descri��o: posicionar a janela em uma determinada posi��o na tela.
  Par�metros de entrada:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console
  Retorno da fun��o:
   -> Nenhum.
 *****************************************************************************************************************/
 void setPosicaoJanela(int top, int left);




 /*****************************************************************************************************************
  Descri��o: definir um titulo para a janela de console.
  Par�metros de entrada:
   -> Uma string contendo o novo t�tulo da janela de console.
  Retorno da fun��o:
   -> Nenhum.
 *****************************************************************************************************************/
 void setTituloConsole(char *);




 /*****************************************************************************************************************
  Descri��o: obter o tamanho da janela de console atual em quantidade de caracteres.
  Par�metros de entrada:
   -> Nenhum.
  Retorno da fun��o:
   -> Estrutura COORD:
      - Campo X representa a largura da janela de console em n�mero de caracteres
      - Campo Y representa a altura da janela de console em n�mero de caracteres

  Observa��o:
   -> A estrutura COORD � inclu�da por meio do arquivo cabe�alho "windows.h". Contudo, a sua declara��o
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que � inclu�do o arquivo
	  cabe�alho "windows.h".
 *****************************************************************************************************************/
 COORD tamanhoJanelaConsole(void);




/****************************************************************************************************************/
/*                                  FIM DAS DECLARA��ES DOS PROT�TIPOS DAS FUN��ES                              */
/****************************************************************************************************************/

#endif
