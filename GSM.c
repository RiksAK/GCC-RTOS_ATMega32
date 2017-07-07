#include "GSM.h"



#include <util/atomic.h>					// подключаем библиотеку для атомарных операций


volatile char buffer[BUF_SIZE]="";
volatile char inbuf[IN_BUF_SIZE]="\0";			//inner buffer of USART
volatile u08 com_detect = 0;					//idex commands
volatile u08 ind_in=0, ind_out=0, rxind_out=0, rxind_in=0, mess = 0;





void SendingData (void){
	
	UDR = buffer[ind_out++];   //запись из буфера
	ind_out &= BUF_MASK;      //проверка маски кольцевого буфера
	if (ind_in == ind_out)  //if last byte //если буфер уже пуст
	{
		UCSRB &= ~(1<<UDRIE); //disable interrupt UDR empty
		RESEN;
	}
}

void RecievingData (void){
	u08 tmp;
	tmp = UDR;
	if (tmp == 0x0d)
	{
		
		inbuf[rxind_in++] = '\0'; //set separate between mess
		rxind_in &= IN_BUF_MASK;
		mess++;     //one more message
		
		
		} else  {
		if (tmp == 0x00) {
			
			} else {
			if (tmp != 0x0a)					//clear bad simble
			{
				inbuf[rxind_in++] = tmp;
				rxind_in &= IN_BUF_MASK;
			}
		}
	}
}

void SendByte(char byte)
{
		//while(!(UCSR0A & (1<<UDRE0))); //Stop interrupt for correct position
		//UDR0 = byte;
	ATOMIC_BLOCK(ATOMIC_FORCEON){
	buffer[ind_in++] = byte; //инкремент «головы» 
	ind_in &= BUF_MASK;  // зацикливание «головы» (организация кольца)
	}
}

void SendStr(char *string)
{
	while (*string !='\r')  //check if End
	{
		SendByte(*string);
		string++;
	}
}

 void Ready_Snd (void)
 {
	 Lcd4_Clear();
	 Lcd4_Set_Cursor(0,1);
	 Lcd4_Write_String ("Ready");
 }

 void ErrMes (void)
 {
	 Lcd4_Clear();
	 Lcd4_Set_Cursor(0,1);
	 Lcd4_Write_String("Error");
 }


 void code_com (u08 count)
 {
	 switch (com_detect)
	 {
		 case (0x12): if (count == 4) com_detect = 2; break; //R^I^N^G
		 case (0x58): if (count == 5) com_detect = 3; break; //ERROR
		 case (0x04): if (count == 2) com_detect = 1; break; //OK
		 case (0x49): if (count == 10) com_detect = 4; break; //Call Ready
		 default: com_detect = 0;
	 }
 }
 
void rx_check_in (void)
{
	char *tmp = 0;
	int count = 0;
	int i = 0;
	com_detect = 0;  //zero command scaner
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String ("Mess in BUF:");
	Lcd4_Set_Cursor(1,13);
	Lcd4_Write_Char(mess+0x30);   //how many mess in buf (ASCII)
	
	while (1)
	{
			
		if (inbuf[rxind_out] != '\0') //if mess separator detected
		{
		
			*tmp = inbuf[rxind_out];
			ATOMIC_BLOCK(ATOMIC_FORCEON){
			com_detect ^= inbuf[rxind_out++];
			rxind_out &= IN_BUF_MASK;
			}
			Lcd4_Set_Cursor(2,i++);
			Lcd4_Write_Char (*tmp);
			count++;
			
		}
		else
		{
			ATOMIC_BLOCK(ATOMIC_FORCEON){
			rxind_out++;
			rxind_out &= IN_BUF_MASK;
			}
			code_com (count);
			break;
		}
	}
	if (com_detect != 0)
	{
		Lcd4_Clear();
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_Char(com_detect + 0x30);
	}
}

int send_sms (int fun, char *number)
{
	int clock = 0;
	UCSRB &= ~(1<<RXEN);   //disable recieve
	SendStr("AT+CMGF=1\r");
	SendByte(CR);
	SEND;
	//Lcd4_Clear();
	//Lcd4_Set_Cursor(1,0);
	//Lcd4_Write_String("Sending to:");
	while (com_detect != 1)
	{
		if (++clock == TIMEOUT)	return 0;
		if (mess != 0) //if we have mess in buffer
		{
			// code
			mess--;   //minus one
			rx_check_in ();
		}
		DELL;
	}
	com_detect = 0;
	clock = 0;
	//Lcd4_Set_Cursor(2,0);
	SendStr("AT+CMGS=\r");
	UCSRB &= ~(1<<RXEN);

	while (*number != '\r')
	{
		SendByte (*number);
		Lcd4_Write_Char (*number);
		number++;
	}
	SendByte(CR);  //send ENTER
	SEND;
	DELL;
	UCSRB &= ~(1<<RXEN);
	if (fun == 1) SendStr(STR_MESS);
	else SendStr(REG_MESS);
	SEND;
	_delay_ms(100);
	UCSRB &= ~(1<<RXEN);
	SendByte(0x1A);
	SEND;
	while (com_detect != 1)
	{
		if ((++clock == TIMEOUT) || (com_detect == 3))	return 0;
		if (mess != 0) //if we have mess in buffer
		{
			// code
			mess--;   //minus one
			rx_check_in ();
		}
		DELL;
	}
	SendByte(0x1B);
	UCSRB &= ~(1<<RXEN);
	SEND;
	Lcd4_Clear();
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String ("Sended");
	_delay_ms(500);
	Ready_Snd();
	return 1;
}




void GsmMain (void)
{
  		  if (mess != 0) //if we have mess in buffer
		  {
			  // code
			  mess--;   //minus one
			  rx_check_in ();
			  if (com_detect == 2)
			  {
				  SendStr("ATH0\r");
				  SendByte(CR);
				  DELL;
				  if (!send_sms (1,NUM0)) ErrMes ();
				   //Ready_Snd ();
			  } else if (com_detect == 4)
			   {
				   if (!send_sms (1,NUM0)) ErrMes ();
				  // Ready_Snd ();
			   }
			  
		  }
		  
	}
	  //return 0;
	
 

