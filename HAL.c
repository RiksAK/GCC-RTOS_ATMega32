#include "HAL.h"


inline void InitAll(void)
{

//InitUSART
          
UBRRL = LO(bauddivider);					// shift the register right by 8 bits
UBRRH = HI(bauddivider);					// set baud rate                         
UCSRB|= (1<<RXCIE);							// enable receive interrupt
UCSRB|= (1<<TXEN)|(1<<RXEN);                // enable receiver and transmitter
UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format

sei ();
/*
====================================================================================
//InitPort
====================================================================================
*/
//LED port
LED_DDR |= 1<<LED1;
//LCD port
LCD_DDR = 0xFF;
//KEYBOARD port
KEYB_PORT |= 1<<COL1|1<<COL2|1<<COL3|1<<ROW1|1<<ROW2|1<<ROW3|1<<ROW4;
KEYB_DDR |= 1<<COL1|1<<COL2|1<<COL3|0<<ROW1|0<<ROW2|0<<ROW3|0<<ROW4;


}



