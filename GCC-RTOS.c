#include "HAL.h"
#include "EERTOS.h"
#include "lcd.h"
#include "GSM.h"
#include "KEYB.h"

//RTOS Interrupt
ISR(RTOS_ISR)
{
	TimerService();
}

//UART Interrupts
//Sending data from buffer
ISR (USART_UDRE_vect)
{
	SendingData();
	sei ();
}


//recieving Data
ISR (USART_RXC_vect)
{
	RecievingData();
	sei ();
}

ISR(USART_TXC_vect)      // ������ ���������� UART - ���������� ��������
{
	sei ();
}


// ��������� ����� ============================================================
void Task1 (void);
void Task2 (void);
void Task3 (void);
void Task4 (void);
void Task5 (void);
void Task6 (void);


//============================================================================
//������� �����
//============================================================================

void Task1 (void)
{
	SetTimerTask(Task2,1000);
	LED_PORT  ^=1<<LED1;
}

void Task2 (void)
{
	SetTimerTask(Task1,1000);
	LED_PORT  &= ~(1<<LED1);
	
}
void Task3 (void)
{
	KeybordScan();
	
	//DisplayKey();
	
	SetTimerTask(Task3,50);
}
void Task4 (void)
{
	//LED_PORT  ^=1<<LED2;
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("NO!");
	SetTimerTask(Task5,1000);
}
void Task5 (void)
{
	Ready_Snd();
	SetTimerTask(Task6,200);
}
void Task6 (void)
{
	GsmMain();
	SetTimerTask(Task6,200);
}

//==============================================================================
int main(void)
{
	InitAll();			// �������������� ���������
	// initialization display
	
	Lcd4_Init();

	InitRTOS();			// �������������� ����
	RunRTOS();			// ����� ����.

	// ������ ������� �����.
	SetTask(Task1);
	SetTask(Task3);
	
	//SetTask(Task3);
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("Hello My Lord!");
	SetTimerTask(Task4,5000);


	while(1) 		// ������� ���� ����������
	{
		wdt_reset();	// ����� ��������� �������
		TaskManager();	// ����� ����������
	}

	return 0;
}
