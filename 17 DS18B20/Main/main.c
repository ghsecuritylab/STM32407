#include "led.h"
#include "lcd.h"
#include "ds18b20.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����17 DS18B20��ʾ�¶�                                               *
* �ļ�������DS18B20ʹ��                                                          *
* �������ڣ�2015.03.15                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����                                                                     *
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/
  
int main(void)
{ 		    
	short temperature;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();       //��ʼ����ʱ����
	LED_Init();					//��ʼ��LED
 	LCD_Init();
  BRUSH_COLOR=RED;    //��������Ϊ��ɫ 
  LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"17.DS18B20 TEST");
	
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_DisplayString(30,130,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill_onecolor(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}   
	LCD_DisplayString(30,130,16,"DS18B20 OK");
	temperature=DS18B20_Get_Temp();  //�ȶ�ȡһ���¶�ֵ
	
	BRUSH_COLOR=BLUE; //��������Ϊ��ɫ 
 	LCD_DisplayString(30,150,16,"Temp:   . C");	 
	while(1)
	{	    	    

			delay_ms(150); //ÿ150ms��ȡһ��	
		
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_DisplayChar(30+40,150,'-',16);			//��ʾ����
				temperature=-temperature;					      //תΪ����
			}
			else 
			  LCD_DisplayChar(30+40,150,' ',16);			//ȥ������
			
			LCD_DisplayNum(30+40+8,150,temperature/10,2,16,0);	//��ʾ��������	    
   		LCD_DisplayNum(30+40+32,150,temperature%10,1,16,0);	//��ʾС������ 		   

	}
}

