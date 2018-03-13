#include "lcd_config.h"
#include "led.h"
#include "usart1.h"
#include "sram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ��F407����ֲSTemWinʵ��                                              *
* �ļ�������STemWin��ֲʵ��                                                      *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������ֲSTemWin��ʾ��Demo                                                * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

int main(void)
{	
	delay_init();       	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//�жϷ�������
  uart1_init(115200);

	LED_Init(); 			      //LED��ʼ��
  LCD_Config_Init();  		//LCD��ʼ��
	Touch_Init();				      //��������ʼ��
  FSMC_SRAM_Init(); 		  //SRAM��ʼ��
	TIM3_Init(999,83); 	    //1KHZ ��ʱ��3����Ϊ1ms
	
	Memory_Init(INSRAM); 		//��ʼ���ڲ��ڴ��
	Memory_Init(EXSRAM);  	//��ʼ���ⲿ�ڴ��
//	
	TIM4_Init(999,839);  //������ɨ���ٶ�,100HZ.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	GUI_DispStringAt("Hello World!", 0, 200);
	GUI_DispStringAt("Hello emWin!", 0, 216);
	
  GUIDEMO_Main();   //�������������л� ֻ���� LCD_Config_Init() �� �޸ĸ�LCD_Display_Dir(1)�Ĳ���ֵ�Ϳ�����  ��0��Ϊ����	 
	while(1)
	{
	}
}

