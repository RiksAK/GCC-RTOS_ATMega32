#ifndef LCD_H_
#define LCD_H_


//LCD Functions Developed by electroSome

#include "HAL.h"


#define RS LCD_RS 
#define EN LCD_EN
#define D4 LCD_D4 
#define D5 LCD_D5
#define D6 LCD_D6
#define D7 LCD_D7



extern void pinChange(int a, int b);
extern void Lcd4_Port(char a);
extern void Lcd4_Cmd(char a);
extern void Lcd4_Clear();
extern void Lcd4_Set_Cursor(char a, char b);
extern void Lcd4_Init();
extern void Lcd4_Write_Char(char a);
extern void Lcd4_Write_String(char *a);
extern void Lcd4_Shift_Right();
extern void Lcd4_Shift_Left();

#endif