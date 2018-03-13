#include "led.h"
#include "lcd.h"
#include "key.h"
/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����4 LCD��ʾ������main.c																						*
* �ļ�������LCD��ʾʵ��																													*
* �������ڣ�2017.08.30																													 *
* ��		����V1.0																																 *
* ��		�ߣ�Clever																															 *
* ˵		����LCD��ʾ�ַ������ֺ�ͼ��																							*
* �Ա����̣�https://shop125046348.taobao.com																		 *
* ��		���������̴��������ѧϰ�ο�																						 *
**********************************************************************************
*********************************************************************************/

void LCD_DispalyInit()
{
	LCD_Clear(WHITE);
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
	LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"4.TFTLCD TEST");
	LCD_DisplayString(50,110,16,"KEY0:Screen Test");	
	LCD_DisplayString(50,130,16,"KEY1:Number Test");	
}

int main(void)
{ 
 	u8 i=0;
	u16 num;
	delay_init();				 //��ʼ����ʱ����	
	LED_Init();						//��ʼ��LED
 	LCD_Init();					 //��ʼ��LCD FSMC�ӿں���ʾ����
	KEY_Init();
	BRUSH_COLOR=RED;			//���û�����ɫΪ��ɫ
		
	while(1) 
	{
		if(i==0)
		{
			LCD_DispalyInit();
			i = 1;
		}
		
		key_scan(0);
		
		if(keydown_data==KEY0_DATA)
			{	
				while(i)
				 {	
						switch(i)
							{							
								case 1:LCD_Clear(BLACK);break;
								case 2:LCD_Clear(BLUE);break;
								case 3:LCD_Clear(RED);break;
								case 4:LCD_Clear(MAGENTA);break;
								case 5:LCD_Clear(GREEN);break;
								case 6:LCD_Clear(CYAN);break; 
								case 7:LCD_Clear(YELLOW);break;
								case 8:LCD_Clear(BRRED);break;
								case 9:LCD_Clear(GRAY);break;
								case 10:LCD_Clear(BROWN);break;
								case 11:LCD_Clear(WHITE);break;
							}								 
							i++;
							LED0=!LED0;	 
							delay_ms(1000);
							if(i>11)
							 { 
								 i=0;
							 }		
					}				 
			}
			else if(keydown_data==KEY1_DATA)
			{
				 LCD_Clear(WHITE);				
				 LCD_DisplayString(20,20,24,"Number Test");		
				 num=8357;
				 LCD_DisplayNum(40,60,num,6,24,0);
				 LCD_DisplayNum(40,90,num,6,24,1);
				 delay_ms(1000);

				 i = 0;
			}
		delay_ms(5);	
	} 
}
