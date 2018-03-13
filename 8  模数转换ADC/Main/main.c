#include "led.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"	 
/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����8 ADCģ��ת��main.c                                              *
* �ļ�������ADCʹ��                                                              *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����                                                                     *
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{ 
 	u8 display_str[8];
	u16 adc_data;
	float temp;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();       //��ʼ����ʱ����
	LED_Init();					//��ʼ��LED 
 	LCD_Init();         //��ʼ��LCD�ӿ�
	ADC1_Init();        //��ʼ��ADC
	BRUSH_COLOR=RED; 
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"8.ADC TEST");

	BRUSH_COLOR=BLUE;//��������Ϊ��ɫ
    
	while(1)
	{ 
		adc_data=Get_Adc(ADC_Channel_5);             //�Ĵ����ĵ�ѹֵ
		sprintf((char*)display_str,"ADC1_CH5_VAL:%06d",adc_data);
		LCD_DisplayString(30,130,16,display_str);	  //��ʾ��Һ����
		temp=(float)adc_data*(3.3/4096);            //ʵ�ʵ�ѹ��ֵ
		sprintf((char*)display_str,"ADC1_CH5_VAL:%06e",temp); //����������  e-01  ���ǳ���10      /10
		LCD_DisplayString(30,150,16,display_str);	  //ʵ�ʵ�ѹ��ֵ

		LED0=!LED0;
		delay_ms(250);	
	}
}
