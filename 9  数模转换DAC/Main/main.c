#include "led.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"	
#include "dac.h"
/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����9 DACʵ���main.c                                                *
* �ļ�������DACʹ��                                                              *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������DAC���ģ���ѹ��ADC��������LCD����ʾ��ѹ����KEY0���������ѹ��    *
            ��KEY1���������ѹ                                                   * 
* �Ա����̣�https://shop125046348.taobao.com                                     *	
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{ 
	u16 adc_data;
	u16 dac_data;
	float temp;
 	u8 display_str[8];	 
	u16 dacval=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();      //��ʼ����ʱ����
	
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��
	ADC1_Init(); 				//adc��ʼ��
	KEY_Init(); 				//������ʼ��
	DAC1_Init();		 		//DACͨ��1��ʼ��	
	BRUSH_COLOR=RED; 
  LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"9.DAC TEST");
	LCD_DisplayString(30,110,16,"KEY0: V++  KEY1:V--");

	BRUSH_COLOR=BLUE;//��������Ϊ��ɫ      	      
 	
  DAC_SetChannel1Data(DAC_Align_12b_R,dacval);//��ʼֵΪ0	
	while(1)
	{
		key_scan(0);			  
		if(keydown_data==KEY0_DATA)
		{		 
			if(dacval<4000)dacval+=200;
			DAC_SetChannel1Data(DAC_Align_12b_R, dacval); //����DACֵ
		}
		else if(keydown_data==KEY1_DATA)	
		{
			if(dacval>200)dacval-=200;
			else dacval=0;
			DAC_SetChannel1Data(DAC_Align_12b_R, dacval); //����DACֵ
		}	 
		
		if(keydown_data==KEY1_DATA||keydown_data==KEY0_DATA) 	//KEY1������
		{	  
 			dac_data=DAC_GetDataOutputValue(DAC_Channel_1);  //��ȡǰ������DAC��ֵ
			sprintf((char*)display_str,"DAC VAL::%06d",dac_data);
			LCD_DisplayString(30,150,16,display_str);	  //��ʾ��Һ����
			temp=(float)dac_data*(3.3/4096);			           //�õ�DAC��ѹֵ
		  sprintf((char*)display_str,"DAC VOL:%06e",temp); //����������  e-01  ���ǳ���10      /10
		  LCD_DisplayString(30,170,16,display_str);	  //ʵ�ʵ�ѹ��ֵ
			
 			adc_data=Get_Adc(ADC_Channel_6);		   //�õ�ADCת��ֵ	  
			temp=(float)adc_data*(3.3/4096);			           //�õ�ADC��ѹֵ			
			sprintf((char*)display_str,"ADC VOL:%06e",temp); //����������  e-01  ���ǳ���10      /10
		  LCD_DisplayString(30,190,16,display_str);	  //ʵ�ʵ�ѹ��ֵ
		}	    
		delay_ms(10);	 
	}	
}
