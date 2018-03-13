#include "usart1.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "rs485.h"
#include "can1.h"
#include "can2.h"
#include "change.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����5 USART1�������������main.c                                     *
* �ļ�������USART1�������ʹ��                                                   *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ������־���USART1����LED�������������գ���KEY0���ڷ�����  *
            �ݵ����ڵ�������                                                     * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{   
	u8 cnt;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init();		      //��ʱ��ʼ�� 
	uart1_init(9600);	    //���ڳ�ʼ��������Ϊ9600
	RS485_Init(9600);
	LED_Init();		  		  //��ʼ����LED 
	BEEP_Init();          //��������ʼ��
  LCD_Init();           //��ʼ��LCD FSMC�ӿں���ʾ����
	BRUSH_COLOR=RED;      //���û�����ɫΪ��ɫ
	
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"5.DATA Change");
 
	/*232��485���õ����ж�ģʽ�������жϽ��պ����д�������ת��
	�����յ�����ʱ��ԭ����485��232��can1����ȥ*/
  
	while(1)
	{		 
		 cnt=CAN1_Receive_Msg(receive_str_can1);
		 Change_can1TO232(cnt);
     Change_can1TO485(cnt);
		 delay_ms(10);
	}
}

