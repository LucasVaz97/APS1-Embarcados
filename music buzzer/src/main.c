/**
 * 5 semestre - Eng. da Computa��o - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */
/* Features{
	plays 2 musics (buttum 1 set furelise,buttum 2 set turkish march buttum 3 plays the music)
	led bliks in music rythm
	oled screen displays the music name
	youtube->https://www.youtube.com/watch?v=_okghWh9GEs
}
music Code references{
	Fur Elise: http://repairmypc.net/2017/08/test-post/
	Turkish March: https://github.com/msamet/Arduino-ile-Mozart-T-rk-Mar-/blob/master/kodlar
}

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/
#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_PIO_IDX      8u
#define LED_PIO_IDX_MASK (1u << LED_PIO_IDX)

#define Buzzer_PIO      PIOA
#define Buzzer_PIO_ID   ID_PIOA
#define Buzzer_PIO_IDX      3u
#define Buzzer_PIO_IDX_MASK (1u << Buzzer_PIO_IDX)


#define button1_PIO           PIOD                 
#define button1_PIO_ID        ID_PIOD                   
#define button1_PIO_IDX       28u                   
#define button1_PIO_IDX_MASK  (1u << button1_PIO_IDX)

#define button2_PIO           PIOC
#define button2_PIO_ID        ID_PIOC
#define button2_PIO_IDX       31u
#define button2_PIO_IDX_MASK  (1u << button2_PIO_IDX)


#define button3_PIO           PIOA
#define button3_PIO_ID        ID_PIOA
#define button3_PIO_IDX       19u
#define button3_PIO_IDX_MASK  (1u << button3_PIO_IDX)



#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
	NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5,
	NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
	NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5,
	NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
	NOTE_A5, NOTE_C6, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5,
	NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5,
	NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
	NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
	NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
	NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
	NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5,
	NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
	NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5,
	NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
	NOTE_A5, NOTE_B5, NOTE_C6,  NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4,
	NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,  NOTE_B5,NOTE_A5,NOTE_GS5,NOTE_FS5,NOTE_GS5,NOTE_A5, NOTE_B5,NOTE_GS5,NOTE_E5,
	NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,  NOTE_B5,NOTE_A5,NOTE_GS5,NOTE_FS5, NOTE_B5,NOTE_GS5,NOTE_E5,NOTE_A5,
	NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,  NOTE_B5,NOTE_A5,NOTE_GS5,NOTE_FS5,NOTE_GS5,NOTE_A5, NOTE_B5,NOTE_GS5,NOTE_E5,
	NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6,  NOTE_B5,NOTE_A5,NOTE_GS5,NOTE_FS5, NOTE_B5,NOTE_GS5,NOTE_E5,NOTE_A5,
	
};
int tempo[] = {
	8, 8, 8, 8, 2,
	8, 8, 8, 8, 2,
	8, 8, 8, 8,
	8,8,8,8,8,8,8,8,2,
	4,4,16,16,16,4,
	4,4,16,16,16,4,4,4,16,16,16,4,4,4,2,
	4,4,4,4,8,8,8,8,2,
	4,4,4,4,8,8,8,8,2,
	4,4,4,4,8,8,8,8,2,
	4,4,4,4,8,8,8,8,2,
	8, 8, 8, 8, 2,
	8, 8, 8, 8, 2,
	8, 8, 8, 8,
	8,8,8,8,8,8,8,8,2,
	4,4,4,4,4,4,4,4,4,4,2,4,8,8,2,
	4,4,2,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,2,4,4,4,4,4,4,4,4,4,4,2,
	4,4,2,4,4,4,4,4,4,4,4,4,4,4,4,
	4,4,2,4,4,4,4,4,4,4,4,4,4,2,
};
int Furmelody[] = {
	NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5,
	NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
	NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4,
	NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4,
	
	NOTE_C5, NOTE_E4, NOTE_E5, NOTE_DS5,
	NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4,
	NOTE_D5, NOTE_C5, NOTE_A4, NOTE_C4,
	NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4,
	
	NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4,
	NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G4,
	NOTE_F5, NOTE_E5, NOTE_D5, NOTE_F4,
	NOTE_E5, NOTE_D5, NOTE_C5, NOTE_E4,
	
	NOTE_D5, NOTE_C5, NOTE_B4, NOTE_E4,
	NOTE_E5, NOTE_E4, NOTE_E5, NOTE_E4,
	NOTE_E5, NOTE_E4, NOTE_E5, NOTE_DS4,
	NOTE_E5, NOTE_D4, NOTE_E5, NOTE_DS4,
	
	NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
	NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4,
	NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4,
	NOTE_C5, NOTE_E4, NOTE_E5, NOTE_DS5,

	NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4,
	NOTE_D5, NOTE_C5, NOTE_A4, NOTE_C4,
	NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4,
	NOTE_C5, NOTE_B4, NOTE_A4, 0,
	
};
int Furtempo[] = {
	9, 9, 9, 9,
	9, 9, 9, 9,
	3, 9, 9, 9,
	3, 9, 9, 9,

	3, 9, 9, 9,
	9, 9, 9, 9,
	9, 9, 3, 9,
	9, 9, 3, 9,

	9, 9, 3, 9,
	9, 9, 3, 9,
	9, 9, 3, 9,
	9, 9, 3, 9,

	9, 9, 9, 9,
	9, 9, 9, 9,
	9, 9, 9, 9,
	9, 9, 9, 9,

	9, 9, 9, 9,
	3, 9, 9, 9,
	3, 9, 9, 9,
	3, 9, 9, 9,

	9, 9, 9, 9,
	9, 9, 3, 9,
	9, 9, 3, 8,
	8, 8, 1, 9,
};

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);
void buzz(long,long);



/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/
void buzz(long frequency, long length) {
	long delayValue = 1000000 / frequency / 2; 
	long numCycles = frequency * length / 1000;
	pio_clear(LED_PIO,LED_PIO_IDX_MASK);
	for (long i = 0; i < numCycles; i++) {
		pio_set(Buzzer_PIO, Buzzer_PIO_IDX_MASK); 
		delay_us(delayValue); 
		pio_clear(Buzzer_PIO, Buzzer_PIO_IDX_MASK); 
		delay_us(delayValue); 
	}
	pio_set(LED_PIO,LED_PIO_IDX_MASK);
}






// Fun��o de inicializa��o do uC
void init(void)
{
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	pmc_enable_periph_clk(button1_PIO_ID);
	pmc_enable_periph_clk(button2_PIO_ID);
	pmc_enable_periph_clk(button3_PIO_ID);
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(Buzzer_PIO_ID);
	
	pio_set_output(LED_PIO,LED_PIO_IDX_MASK,0,0,0);
	pio_set_input(button1_PIO, button1_PIO_IDX_MASK,PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_input(button2_PIO, button2_PIO_IDX_MASK,PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_input(button2_PIO, button3_PIO_IDX_MASK,PIO_PULLUP);
	pio_set_output(Buzzer_PIO,Buzzer_PIO_IDX_MASK,0,0,0);
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas n�o devem sair do while(1).
  Bool musica=0;
  int toPlay=0;
  board_init();
	sysclk_init();

	delay_init();
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);
	pmc_enable_periph_clk(ID_PIOD);
	pmc_enable_periph_clk(ID_SPI0);
	
	gfx_mono_ssd1306_init();
	
  while (1){
	  		  
	  if(!pio_get(button3_PIO,PIO_INPUT,button3_PIO_IDX_MASK) && musica==0){
		  
	  musica=1;}
	  if(!pio_get(button2_PIO,PIO_INPUT,button2_PIO_IDX_MASK)){
		  gfx_mono_draw_string("MarchaTurka", 20,16, &sysfont);
		  toPlay=1;}
	  if(!pio_get(button1_PIO,PIO_INPUT,button1_PIO_IDX_MASK)){
		  gfx_mono_draw_string("FurElise  ", 20,16, &sysfont);
		  toPlay=0;}
	  
	  if(musica && toPlay==0){
		  int size = sizeof(Furmelody) / sizeof(int);
		  for (int thisNote = 0; thisNote < size; thisNote++){
			  int noteDuration =(1000 / Furtempo[thisNote]);
			  buzz(Furmelody[thisNote], noteDuration);
			  int pauseBetweenNotes = (noteDuration * 1.30);
			  delay_ms(pauseBetweenNotes);
			  buzz(0, noteDuration);
			  if(!pio_get(button3_PIO,PIO_INPUT,button3_PIO_IDX_MASK)){
				  musica=0;
				  thisNote=size;
			  }
			  }
			musica=0;
			
	  }
	  
	  if(musica && toPlay==1){
		  int size = sizeof(melody) / sizeof(int);
		  for (int thisNote = 0; thisNote < size; thisNote++){
			  int noteDuration =(1000 / tempo[thisNote]);
			  buzz(melody[thisNote], noteDuration);
			  int pauseBetweenNotes = (noteDuration * 0.2);
			  delay_ms(pauseBetweenNotes);
		  buzz(0, noteDuration);}
		  musica=0;
	  }
  }
		 
			
return 0;
}
