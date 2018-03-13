#include "usart1.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "key.h"

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init();		      //��ʱ��ʼ�� 
	uart1_init(9600);	    //���ڳ�ʼ��������Ϊ9600
	KEY_Init();
	LED_Init();		  		  //��ʼ����LED 
	BEEP_Init();          //��������ʼ��
  LCD_Init();           //��ʼ��LCD FSMC�ӿں���ʾ����
	BRUSH_COLOR=RED;      //���û�����ɫΪ��ɫ
	
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"5.USART1 TEST");
	LCD_DisplayString(50,110,16,"Please send control cmd");
  
	while(1)
	{
		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		  {
		    /*��printf()֮��ĺ�����ʹ���˰�����ģʽ��ʹ�ñ�׼��ᵼ�³����޷�
          ����,�����ǽ������:ʹ��΢��,��Ϊʹ��΢��Ļ�,����ʹ�ð�����ģʽ. 
          ���ڹ������Եġ�Target��-����Code Generation���й�ѡ��Use MicroLIB����
          ���Ժ�Ϳ���ʹ��printf��sprintf������*/
				printf("���ڴ�ӡ����\r\n");
				uart1SendChars("UART1 TEST\r\n",13);
		  }
	}
}

