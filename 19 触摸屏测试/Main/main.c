 #include "usart1.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "touch.h" 


/*********************************************************************************
*************************MCU���� STM32F407����Ӧ�ð�******************************
**********************************************************************************
* �ļ�����: ����19 ������main.c                                                  *
* �ļ�������������ʵ��һ����ͼ��                                                 *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����������ʵ��һ����ͼ��                                                 *    
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/	


//�����Ļ
void Clear_Screen(void)
{
	LCD_Clear(WHITE);//����   
 	BRUSH_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_DisplayString(lcd_width-40,lcd_height-18,16,"Clear");//��ʾ��������
  BRUSH_COLOR=RED;//���û�����ɫ 
}

//���败�������Ժ���
void R_Touch_test(void)
{
	u8 i=0;	  
	while(1)
	{
	 	key_scan(0);
		RTouch_Scan(0); 		 
	
		 	if(Xdown<lcd_width&&Ydown<lcd_height)
			{	
				if(Xdown>(lcd_width-40)&&Ydown>lcd_height-18)Clear_Screen();  //�����Ļ
				else Draw_Point(Xdown,Ydown,RED);		//��ͼ	  			   
			}   
		i++;
		if(i%20==0)LED0=!LED0;
	}
}

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();  //��ʼ����ʱ����
	uart1_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	Touch_Init();				//��������ʼ��
 	BRUSH_COLOR=RED;    //��������Ϊ��ɫ 
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"19.TOUCH TEST");

	delay_ms(1000);
	
 	Clear_Screen();	 	
  R_Touch_test(); 					  //������������Բ���
}
