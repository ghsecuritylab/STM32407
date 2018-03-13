#include "led.h"
#include "beep.h" 
#include "lcd.h"
#include "key.h"
#include "rs485.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����10 USART2����RS485�������������main.c                             *
* �ļ�������USART2�������ʹ��                                                   *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ������־���USART2����LED�������������գ���KEY0���ڷ�����  *
            �ݵ����ڵ�������                                                     * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
**********************************************************************************
*********************************************************************************/

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();       //��ʼ����ʱ����
	
	LED_Init();					//��ʼ��LED 
	BEEP_Init();        //��ʼ��������
 	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	RS485_Init(9600);		//��ʼ��RS485����2
 	BRUSH_COLOR=RED;    //��������Ϊ��ɫ 
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"10.USART2 TEST");	
	LCD_DisplayString(30,130,16,"KEY0:Send");    	//��ʾ��ʾ��Ϣ		
 									  
	while(1)
	{
		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		  {
		   RS485_Send_Data("UART2 TEST",11);
		  }
	}  
}

