//
//  Tastenblinky.c
//  Tastenblinky
//
//  Created by Sysadmin on 03.10.07.
//  Copyright Ruedi Heimlihcer 2007. All rights reserved.
//



#include <avr/io.h>
#include <avr/delay.h>
//#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
//#include <avr/sleep.h>
#include <inttypes.h>
//#define F_CPU 4000000UL  // 4 MHz
#include <avr/delay.h>
#include "adc.c"

#include "defines.h"

#include "display.c"

#include "text.h"



uint16_t loopCount0=0;
uint16_t loopCount1=0;
uint16_t loopCount2=0;

uint16_t spicounter=0;

#define TWI_PORT		PORTC
#define TWI_PIN		PINC
#define TWI_DDR		DDRC

#define SDAPIN		4
#define SCLPIN		5



volatile uint8_t					Programmstatus=0x00;

volatile uint16_t laufsekunde=0;
volatile uint8_t laufminute=0;
volatile uint8_t laufstunde=0;

volatile uint16_t motorsekunde=0;

volatile uint16_t motorminute=0;

volatile uint16_t stopsekunde=0;

volatile uint16_t stopminute=0;
volatile uint16_t batteriespannung =0;
volatile uint16_t updatecounter =0;


volatile uint16_t                manuelltrimmcounter=0; // Counter fuer Timeout der Trimmtsastatur


volatile uint8_t                 curr_screen=0; // aktueller screen
volatile uint8_t                 curr_cursorzeile=0; // aktuelle zeile des cursors
volatile uint8_t                 curr_cursorspalte=0; // aktuelle colonne des cursors
volatile uint8_t                 last_cursorzeile=0; // letzte zeile des cursors
volatile uint8_t                 last_cursorspalte=0; // letzte colonne des cursors


volatile uint16_t                posregister[8][8]={}; // Aktueller screen: werte fuer page und daraufliegende col fuer Menueintraege (hex). geladen aus progmem

volatile uint16_t                cursorpos[8][8]={}; // Aktueller screen: werte fuer page und darauf liegende col fuer den cursor
volatile uint16_t                 blink_cursorpos=0xFFFF;

void spi_init(void) // SPI-Pins aktivieren
{
   // https://embedds.com/serial-peripheral-interface-in-avr-microcontrollers/
   //set MOSI, SCK and SS as output
   DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB2);
   //set SS to high
   PORTB |= (1<<PB2);
   //enable master SPI at clock rate Fck/16
   SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
   }


void slaveinit(void)
{
   
   //LCD
   LOOPLED_DDR |= (1<<LOOPLED_PIN);
   spi_init();
   _delay_ms(1);
   
   OSZIDDR |= (1<<OSZI_PULS_A);
   OSZIPORT |= (1<<OSZI_PULS_A);
   OSZIDDR |= (1<<OSZI_PULS_B);
   OSZIPORT |= (1<<OSZI_PULS_B);
   
   
   
   DOG_SPI_DDR |= (1<<DOG_SPI_CS);
   DOG_SPI_DDR |= (1<<DOG_SPI_A0);
   DOG_SPI_DDR |= (1<<DOG_SPI_RST);
   
   DOG_SPI_PORT |= (1<<DOG_SPI_CS); // HI
   DOG_SPI_PORT |= (1<<DOG_SPI_A0); // HI
   DOG_SPI_PORT |= (1<<DOG_SPI_RST);

   
   _delay_ms(5);
   display_init();
   
   
}

int main (void)
{
	
	
	
	slaveinit();
	_delay_ms(1000);
	uint8_t i=0;

   display_go_to(16,8);
   
   //display_akkuanzeige(24);
   
   //sethomescreen();
   char_x = 24;
   char_y = 4;
   display_go_to(char_x,char_y);
   setlogscreen();
// MARK: while
	while (1) 
	{
		
		loopCount0 ++;
		//_delay_ms(2);
		
		if (loopCount0 >=0xFFFE)
		{
         loopCount0 = 0;
			//LOOPLED_PORT ^= (1<<LOOPLED_PIN);
			loopCount1++;
			
			if ((loopCount1 >0xFFFE)  )
			{
            loopCount2++;
            if(loopCount2 >0x03)
				{
               loopCount2=0;
               //OSZI_B_TOGG();
               //display_go_to(16,8);
               //display_write_int(i++,2);
					LOOPLED_PORT ^= (1<<LOOPLED_PIN);
               
               char_x=RANDLINKS+100;
               char_y = 1;
               char_height_mul = 1;
               char_width_mul = 1;
               display_go_to(char_x+1,2);
               //display_write_int(i++,2);
               
               //update_time();
               display_write_min_sek(motorsekunde , 1);
               
               motorsekunde++;
               if(motorsekunde > 59)
               {
                  motorsekunde = 0;
                  motorminute++;
               }
               
					
				}
            
			}
			
			loopCount0 =0;
		}
		
      
      
	} // while
	
	
	return 0;
}
