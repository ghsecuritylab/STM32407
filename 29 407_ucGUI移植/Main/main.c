#include "led.h"
#include "lcd_config.h"
#include "key.h"
#include "timer.h"
#include "gui.h"
#include "touch.h" 
#include "GUIDEMO.h"
/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ��F407����ֲucGUIʵ��                                                *
* �ļ�������ucGUI��ֲʵ��                                                        *
* �������ڣ�2017.08.05                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������ֲucGUI��ʾ��Demo                                                  * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/


int main(void)
{ 
	delay_init();         //��ʼ����ʱ����	
	LED_Init();					  //��ʼ��LED
	KEY_Init();
	TIM3_Init(999,83); 	//1KHZ ��ʱ��3����Ϊ1ms
	TIM4_Init(999,839);  //������ɨ���ٶ�,100HZ.
	Touch_Init();
	GUI_Init();
//	GUI_SetFont(&GUI_Font8x16);
//	GUI_SetColor(GUI_WHITE);   
//	
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetBkColor(GUI_BLACK);
//	GUI_Clear();
//  GUI_SetFont(&GUI_Font24_ASCII);
//  GUI_DispStringHCenterAt("COLOR_ShowColorBar - Sample", 160, 4);
	while(1) 
	{		 
	  GUIDEMO_main();  //����GUIDEMO	
	} 
}
