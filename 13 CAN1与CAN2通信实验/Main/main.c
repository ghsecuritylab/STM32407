#include "led.h"
#include "lcd.h"
#include "key.h"
#include "can1.h"
#include "can2.h"
#include "usart1.h"

/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����13 CANͨ��ʵ��                                                   *
* �ļ�������canͨ��                                                              *
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
	u8 CAN1_mode=0; //CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	u8 CAN2_mode=0; //CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	
	u8 can1_sendbuf[8]="CAN1SEND";
	u8 can2_sendbuf[8]="CAN2SEND";
	
	u8 can1_RECbuf[8]={0};
	u8 can2_RECbuf[8]={0};
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();    //��ʼ����ʱ����
	LED_Init();			 //��ʼ��LED 
 	LCD_Init();			 //LCD��ʼ�� 
	KEY_Init(); 		 //������ʼ��  
	uart1_init(9600);
	
	CAN1_Mode_Init(CAN1_mode);//CAN��ʼ����ͨģʽ,������500Kbps   ����canͨ��
  CAN2_Mode_Init(CAN2_mode);//CAN��ʼ����ͨģʽ,������500Kbps 
  //������Ϊ:42M/((1+6+7)*6)=500Kbps	
 	
 	BRUSH_COLOR=RED;//��������Ϊ��ɫ 
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");
	LCD_DisplayString(30,60,24,"13.CAN TEST");

    CAN1_Send_Msg(can1_sendbuf,8);//����8���ֽ�   
	  delay_ms(10);
	  CAN2_Receive_Msg(can2_RECbuf); 
	  LCD_DisplayString(30,120,24,can2_RECbuf);   //Һ������ʾcan2���յ�����ֵ
	  uart1SendChars(can2_RECbuf,8);  //���ڷ���can2���յ�����ֵ
  
/**************************************************************************************/

    CAN2_Send_Msg(can2_sendbuf,8);//����8���ֽ�   
    delay_ms(10);	
	  CAN1_Receive_Msg(can1_RECbuf); 
		LCD_DisplayString(30,180,24,can1_RECbuf); //Һ������ʾcan1���յ�����ֵ
	  uart1SendChars(can1_RECbuf,8);     //���ڷ���can1���յ�����ֵ
 									  
while(1)
	{
		delay_ms(100);
		LED0=!LED0;//��ʾϵͳ��������	   
	} 
}

