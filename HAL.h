#ifndef HAL_H
#define HAL_H

#ifndef F_CPU
#define F_CPU 16000000L					// 16 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avrlibtypes.h"
#include "avrlibdefs.h"
#include "avrlibtypes.h"
#include "avr/pgmspace.h"
#include <avr/wdt.h>
#include <util/delay.h>


//Clock Config
//#define F_CPU 16000000L



//System Timer Config
#define Prescaler	  		64
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS


//USART Config
#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)


//PORT Defines
#define LED1 		4
//#define LED2		5
//#define	LED3		7

//#define I_C			3
//#define I_L			6
#define LED_PORT 	PORTC
#define LED_DDR		DDRC

//LCD Defines

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7


#define LCD_PORT 	PORTD
#define LCD_DDR		DDRD

//Keyboard Defines




/*
#define ROW1  0
#define COL1  1
#define ROW4  2
#define COL3  3
#define ROW3  4
#define ROW2  5
#define COL2  6
*/

#define COL2  DDB6
#define ROW1  PINB0
#define COL1  DDB1
#define ROW4  PINB2
#define COL3  DDB3
#define ROW3  PINB4
#define ROW2  PINB5

#define KEYB_PORT 	PORTB
#define KEYB_PIN	PINB
#define KEYB_DDR	DDRB


extern void InitAll(void);



#endif
