#include "led.h"
#include "lcd.h"
#include "24c02.h"
#include "key.h"  
#include "usart1.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����11 24C02ͨ��������main.c                                         *
* �ļ�������24C02ʹ��                                                            *
* �������ڣ�2015.03.09                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ���������Ƭ���������ݣ���ͨ����KEY0д��24c02����KEY1����  *
            д�������                                                           * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

 
int main(void)
{ 
	u8 i=0;
	u8 *datatemp;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();       //��ʼ����ʱ����
	uart1_init(9600);   //���ڳ�ʼ��
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	AT24C02_Init();			//AT24C02��ʼ�� 
	
 	BRUSH_COLOR=RED;   //��������Ϊ��ɫ
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"11.24C02 TEST");  
	
  LCD_DisplayString(30,110,16,"Please send data to usart1 ");   
  LCD_DisplayString(30,130,16,"Usart1 receive data is:"); 
  LCD_DisplayString(10,170,16,"KEY0:Write rec_data to 24c02");
	LCD_DisplayString(10,190,16,"KEY1:Read before write data ");
 	BRUSH_COLOR=BLUE;  //��������Ϊ��ɫ	  
	while(1)
	{
		key_scan(0);
		if(keydown_data==KEY0_DATA)//KEY0����,������1���յ�������д��24C02
		{  
 			LCD_Fill_onecolor(0,210,239,249,WHITE);
			LCD_DisplayString(30,210,16,"Start write 24C02....");
			AT24C02_Write(0,(u8*)receive_str,uart_byte_count);
			LCD_DisplayString(30,210,16,"24C02 write finished!");//д��ɹ�
		}
		if(keydown_data==KEY1_DATA)//KEY1����,��д�뵽24C02�е����ݶ�������ʾ
		{
 			LCD_DisplayString(30,210,16,"Start read 24C02.... ");
			AT24C02_Read(0,datatemp,uart_byte_count);
			LCD_DisplayString(30,210,16,"The readed data is:  "); 
			LCD_DisplayString(30,230,16,datatemp);          //��ʾ����������
		}	 
			i++;
			delay_ms(10);
			if(i==50||i==100)
			{
				if(i==50)
				 {
					LED0=0;
					LCD_DisplayString(30,110,16,"                           ");
				 }
				 if(i==100)
				 {
					LED0=1;
					LCD_DisplayString(30,110,16,"Please send data to usart1 ");   
					i=0;
				 }
				
			}		   
	} 	    
}
