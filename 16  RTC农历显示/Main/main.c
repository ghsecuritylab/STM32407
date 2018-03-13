#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "malloc.h" 
#include "tfcard_sdio.h"    
#include "malloc.h" 
#include "w25qxx.h"    
#include "ff.h"     
#include "updatefont.h"  //����HanZiUse.lib�и����ֿ⺯��
#include "showhz.h"	     //����HanZiUse.lib����ʾ���ֺ���

#include "rtc.h"
#include "lucalendar.h"   
/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����16 RTCũ����ʾ                                                   *
* �ļ�������RTCʹ��                                                              *
* �������ڣ�2015.03.15                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����������KEY3����ʱ���������KEY0������ֵ�ļ�1����KEY1��ֵ���м�1��     *
            ��KEY2����ѡ��Ҫ���õ�ѡ��ڵ������̰�KEY3��ȷ�ϵ���ʱ��         *
* �Ա����̣�https://shop125046348.taobao.com                                     *		
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

u8 const *weekdate[7]={"һ","��","��","��","��","��","��"};
u8 const *set_option[6]={"Year","Month","Day","Hours","Minutes","Seconds"};

//lcd����ʾʱ��
void Time_Display()
{
	
 LCD_DisplayHZstr(30,210,16,"����:20  -  -  ");
 LCD_DisplayNum(86,210,RTC_DateStruct.RTC_Year,2,16,1);
 LCD_DisplayNum(110,210,RTC_DateStruct.RTC_Month,2,16,1);
 LCD_DisplayNum(134,210,RTC_DateStruct.RTC_Date,2,16,1);
 LCD_DisplayHZstr(30,230,16,"ʱ��:  :  :  ");
 LCD_DisplayNum(70,230,RTC_TimeStruct.RTC_Hours,2,16,1);	
 LCD_DisplayNum(94,230,RTC_TimeStruct.RTC_Minutes,2,16,1);
 LCD_DisplayNum(118,230,RTC_TimeStruct.RTC_Seconds,2,16,1);
 LCD_DisplayHZstr(30,250,16,"����:        ");
 LCD_DisplayHZstr(70,250,16,(u8 *)weekdate[RTC_DateStruct.RTC_WeekDay-1]);
}
void Adjust_Time(u8 option,u8 shanshuo)
{
		if(shanshuo%50==0)  //��ʾ����Ҫ���õ�ѡ��
	  {
			LCD_DisplayString_color(20,180,24,"Please Set          ",BLUE,WHITE);
		  LCD_DisplayString_color(152,180,24,(u8 *)set_option[option],BLUE,WHITE);
		}
		
		//����ʱ��ֵ�ļӼ�1  Calendar
		if( (keydown_data==KEY0_DATA)||(keydown_data==KEY1_DATA))
		{
		  if(keydown_data==KEY0_DATA)
			{
			  switch(option)
				{
				  case 0: RTC_DateStruct.RTC_Year+=1;   break;
					case 1: RTC_DateStruct.RTC_Month+=1;  break;
					case 2: RTC_DateStruct.RTC_Date+=1;   break;
					case 3: RTC_TimeStruct.RTC_Hours+=1;  break;
					case 4: RTC_TimeStruct.RTC_Minutes+=1;break;
					case 5: RTC_TimeStruct.RTC_Seconds+=1;break;
				}	
			}
			if(keydown_data==KEY1_DATA)
			{
			  switch(option)
				{
				  case 0: RTC_DateStruct.RTC_Year-=1;   break;
					case 1: RTC_DateStruct.RTC_Month-=1;  break;
					case 2: RTC_DateStruct.RTC_Date-=1;   break;
					case 3: RTC_TimeStruct.RTC_Hours-=1;  break;
					case 4: RTC_TimeStruct.RTC_Minutes-=1;break;
					case 5: RTC_TimeStruct.RTC_Seconds-=1;break;
				}	
			}
		}
		//��˸��ʾ����ʾ
	if(shanshuo==150)
		{
			Time_Display();
//			LCD_DisplayNum(86,220,RTC_DateStruct.RTC_Year,2,16,1);
//			LCD_DisplayNum(110,220,RTC_DateStruct.RTC_Month,2,16,1);
//			LCD_DisplayNum(134,220,RTC_DateStruct.RTC_Date,2,16,1);
//			LCD_DisplayNum(70,240,RTC_TimeStruct.RTC_Hours,2,16,1);
//			LCD_DisplayNum(94,240,RTC_TimeStruct.RTC_Minutes,2,16,1);
//			LCD_DisplayNum(118,240,RTC_TimeStruct.RTC_Seconds,2,16,1);
		}	
		//��˸��ʾ������ʾ
	switch(option)
	  {  
			case 0: {  if(shanshuo==49)  LCD_DisplayString(86,210,16,"  ");	 break;  }
			case 1: {  if(shanshuo==49)  LCD_DisplayString(110,210,16,"  "); break;  }
			case 2: {  if(shanshuo==49)  LCD_DisplayString(134,210,16,"  "); break;  }
			case 3: {  if(shanshuo==49)  LCD_DisplayString(70,230,16,"  ");  break;  }
			case 4: {	 if(shanshuo==49)  LCD_DisplayString(94,230,16,"  ");	 break;	 }
			case 5: {	 if(shanshuo==49)  LCD_DisplayString(118,230,16,"  "); break;  }		
	  }
}	
int main(void)
{   
	u8 process=0;  //������������
  u8 option;     //����ʱ��ѡ��
	u8 t=0,j;      //��ʱ����
	u8 *nonglibuf;
  u8 *jieqibuf;
	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();         //��ʼ����ʱ����
	LED_Init();					  //��ʼ��LED
 	LCD_Init();					  //��ʼ��LCD
	KEY_Init();           //��ʼ��KEY
	RTC_InitConfig();		 	//��ʼ��RTC
	W25QXX_Init();         
	
	font_init();   //�ֿ��ʼ�� ֮�������ʾ����  ����ȷ��W25Q128�����Ѿ����ֿ�
	
	Memory_Init(INSRAM);	
	nonglibuf=(u8 *)Mem_malloc(INSRAM,50);  //�����ָ���������ֵַ����Ȼ��һ��ָ������ܻ�ñ��������˵�ֵַ���ڶ�����ûֵ(����������)
	jieqibuf=(u8 *)Mem_malloc(INSRAM,50);
	
	BRUSH_COLOR=RED;
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayHZstr(30,70,24,"14.RTCũ����ʾ");
	LCD_DisplayHZstr(30,100,16,"KEY3 ���� :����ʱ��");
	LCD_DisplayHZstr(30,120,16,"     �̰� :ȷ�ϵ���");
	LCD_DisplayHZstr(30,140,16,"KEY0:��1  KEY1: ��1");
	LCD_DisplayHZstr(30,160,16,"KEY2:����һλ");
	
	RTC_GetTimes(RTC_Format_BIN);
	Time_Display();
  	while(1) 
	{		
		key_scan(0);	
		t++;

		switch(process)
		{
			case 0:   // ����0��ʱ����ʾ
			     {
						 if(key_tem==KEY3_DATA&&key_time>250)
							{
								process=1;   //����KEY3 �������ʱ������
								break;
							}
						 if((t%50)==0)	//ÿ250ms������ʾ
							{
								RTC_GetTimes(RTC_Format_BIN);
								Time_Display();
								GetLunarCalendarStr(RTC_DateStruct.RTC_Year+2000,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date,nonglibuf);
                LCD_DisplayHZstr(30,270,16,nonglibuf);
	
                GetJieQiStr(RTC_DateStruct.RTC_Year+2000,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date,jieqibuf);
                LCD_DisplayHZstr(30,290,16,jieqibuf);
							} 
						break;
			     }
			case 1:    // ����1������ʱ��
					{
					  if(keydown_data==KEY2_DATA) //��KEY2ѡ������
						  {
						   option++;
							 if(option>5)   //ѭ��
								 option=0;
						  }					
						Adjust_Time(option,t);//����ʱ�亯��
						 if(keydown_data==KEY3_DATA)
						 {
						   Time_Display();// ��ֹ����˸����ʾ��ʱ�򣬶̰�KEY3ȷ�ϵ����� ��ʾ��
							 RTC_SetTimes(RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date,RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds);
							 //����ʱ����Ҫ5�������ң���ʱ���һ��
							 LCD_DisplayString_color(20,180,24,"Adjust OK          ",BLUE,WHITE);
							 for(j=0;j<100;j++) delay_ms(10);  // Adjust OK ����OK��ʾ1��
							 LCD_DisplayString(20,180,24,"                    ");
							 option=0;    //ѡ���ͷ��
							 process=0;   //�̰�KEY3ʱ��������� ���ص�ʱ����ʾ
							 break;
						 }
 						break;
					}
	  }
		delay_ms(5); //ϵͳ��ʱ��Ҳ����ϵͳ��ʱ
	}	
}





