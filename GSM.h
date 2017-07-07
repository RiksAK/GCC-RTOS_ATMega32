#ifndef GSM_H_
#define GSM_H_

#include "HAL.h"


#define BUF_SIZE 128						// размер буфера передатчика
#define BUF_MASK (BUF_SIZE-1)
#define IN_BUF_SIZE 64					// размер буфера приемника
#define IN_BUF_MASK (IN_BUF_SIZE-1)

#define CR 0x0D
#define SUB 0x0A

#define DELL _delay_ms (500)

#define SEND (UCSRB |= (1<<UDRIE)) // разрешаем прерывание по опустошению регистра передатчика
#define RESEN (UCSRB |= (1<<RXEN)) // RX Enable

#define NUM0 "\"+380667677998\"\r"
#define REG_MESS "Hello. Button 1\r"
#define STR_MESS "Device ready to work\r"


#define TIMEOUT 100

extern void Lcd4_Clear();
extern void Lcd4_Set_Cursor(char a, char b);
extern void Lcd4_Write_Char(char a);
extern void Lcd4_Write_String(char *a);
void SendByte (char byte);
void SendStr (char *string);
void code_com (u08 count);
void Ready_Snd (void);
void ErrMes (void);
void rx_check_in (void);
void SendingData (void);
void RecievingData (void);
int send_sms (int fun, char *number);
void GsmMain (void);

#endif /* GSM_H_ */