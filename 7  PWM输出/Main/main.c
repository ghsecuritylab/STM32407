#include "led.h"
#include "lcd.h"
#include "key.h"
#include "pwm.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����7 PWM���������main.c                                            *
* �ļ�������PWM���                                                              *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �����������������ͬռ�ձȵ�PWM��,��ʾ�����۲�                           *
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{ 
  u32 pwmzkb;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();		      //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED 
	KEY_Init();
	LCD_Init();
	BRUSH_COLOR=RED;      //���û�����ɫΪ��ɫ
	
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"7.PWM TEST");	
	LCD_DisplayString(30,110,16,"KEY0:dutyfactor-- ");
	LCD_DisplayString(30,130,16,"KEY1:dutyfactor++ ");
	LCD_DisplayString(30,150,16,"Now dutyfactor is 50%");
	
	TIM5_PWM_Init(499,83);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.  
  pwmzkb=250;
  TIM_SetCompare1(TIM5,pwmzkb);		
	while(1)
	{
		key_scan(0);
    if(keydown_data==KEY0_DATA) 
		  {
		   pwmzkb-=50;
				if(pwmzkb<50)pwmzkb=50;
			 TIM_SetCompare1(TIM5,pwmzkb);	 // �޸�ռ�ձ�        
			}
		if (keydown_data==KEY1_DATA) 
			{
				pwmzkb+=50;
				if(pwmzkb>450)pwmzkb=450;
				TIM_SetCompare1(TIM5,pwmzkb);  // �޸�ռ�ձ�  
			}  
    delay_ms(10); 			
	}
}


