#ifndef KEYB_H_
#define KEYB_H_

#include "HAL.h"

#define CODE_SIZE 6

extern void Lcd4_Set_Cursor(char a, char b);
extern void Lcd4_Write_Char(char a);
void KeybordScan (void);
void DisplayKey (void);

#endif /* KEYB_H_ */