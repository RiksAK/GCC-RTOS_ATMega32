#include "KEYB.h"

volatile char pressed_key[CODE_SIZE+1]="\0";	//code container
volatile char temp_symbol;						//container of has been key pressed  
char key_code[3][4]={{'1','4','7','*'},			//array of key value
					 {'2','5','8','0'},
					 {'3','6','9','#'}};
						 
volatile u08 count_symbol = 0, count_pressed=0, i = 0, j = 0;

void DisplayKey (void)
	{
	volatile int k=0;
	volatile char *tmp = 0;
	
	Lcd4_Set_Cursor(2,0);
	for (k=0; k!=7; k++)
	{
		*tmp = pressed_key[k];
		Lcd4_Write_Char (*tmp);
		
	}
	//count_symbol = 0;
}

void ClearPressed (void)
	{
	
	char cle = '\0';
	while (count_symbol != 0)
	{
		pressed_key[count_symbol-1] = cle;
		count_symbol--;
	}

}

void RecordSymol (char symbol){
	
	
	if (pressed_key[count_symbol-1] != symbol)
	{
		pressed_key[count_symbol++] = symbol;
		count_pressed = 0;
		
	}
	else
	{
		count_pressed++;
		
	}
	
	if (count_pressed == 3)
	{
		
		pressed_key[count_symbol++] = symbol;
		count_pressed = 0;
		
	}
	
	if (count_symbol == 7)
	{
		
	ClearPressed();
		
	}
}




void ScanRow (void){
	u08 tmp;
	tmp = KEYB_PIN;
	
	if (!(tmp & (1<<ROW1))){
		j=0;
		temp_symbol = key_code[i][j];
		RecordSymol(temp_symbol);
		}
		 if (!(tmp & (1<<ROW2))){
		j=1;
		temp_symbol = key_code[i][j];
		RecordSymol(temp_symbol);
		}
		if (!(tmp & (1<<ROW3))){
		j=2;
		temp_symbol = key_code[i][j];
		RecordSymol(temp_symbol);
		}
		 if (!(tmp & (1<<ROW4))){
		j=3;
		temp_symbol = key_code[i][j];
		RecordSymol(temp_symbol);
		}
}

void KeybordScan (void){
	
	
	for (i=0; i<3; i++)
	{
		switch (i) {
			case 0:
			KEYB_PORT  &= ~(1<<COL1);
			_delay_ms(10);
			ScanRow();
			KEYB_PORT  ^= 1<<COL1;
			break;
			
			case 1:
			KEYB_PORT  &= ~(1<<COL2);
			_delay_ms(10);
			ScanRow();
			KEYB_PORT  ^= 1<<COL2;
			break;
			
			case 2:
			KEYB_PORT  &= ~(1<<COL3);
			_delay_ms(10);
			ScanRow();
			KEYB_PORT  ^= 1<<COL3;
			break;
			
			default:
			
			break;
		}
		
		DisplayKey();
	}
	

	
	 
}


