#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "w25qxx.h"  
#include "usart1.h"
#include "tfcard_sdio.h"
#include "ff.h"    
#include "updatefont.h"
#include "showhz.h"	
#include "usbhost_user.h" 


/*********************************************************************************
**********************MCU���� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: ����21 U��OTG main.c                                                 *
* �ļ�������U��OTG                                                               *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ������ȡU��������                                                        * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************�B
*********************************************************************************/  


USBH_HOST  USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;


//�û�����������
//����ֵ:0,����
//       1,������
u8 USH_User_App(void)
{ 
	u32 total,free;
	u8 res=0;
	LCD_DisplayHZstr(30,140,16,"�豸���ӳɹ�!.");	 
	res=getUfree_volume("2:",&total,&free);
	if(res==0)
	{
		BRUSH_COLOR=BLUE;//��������Ϊ��ɫ	   
		LCD_DisplayString(30,160,16,"FATFS OK!");	
		LCD_DisplayString(30,180,16,"U Disk Total Size:     MB");	 
		LCD_DisplayString(30,200,16,"U Disk  Free Size:     MB"); 	    
		LCD_DisplayNum(174,180,total>>10,5,16,0); //��ʾU�������� MB
		LCD_DisplayNum(174,200,free>>10,5,16,0);	
	} 
 
	while(HCD_IsDeviceConnected(&USB_OTG_Core))//�豸���ӳɹ�
	{	
		LED1=!LED1;
		delay_ms(200);
	}
	BRUSH_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_DisplayHZstr(30,140,16,"�豸������...");
	LCD_Fill_onecolor(30,160,239,220,WHITE);
	return res;
} 


int main(void)
{        
	u8 t;
	FATFS *fsUP;  //U���ļ�ϵͳ	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
 	delay_init();        //��ʼ����ʱ����
	uart1_init(9600);	 	 //��ʼ�����ڲ�����Ϊ9600   
	LED_Init();				   //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				   //����
  LCD_Init();				   //��ʼ��LCD 
	W25QXX_Init();			 //SPI FLASH��ʼ��
	Memory_Init(INSRAM); //��ʼ���ڲ��ڴ��	

	fsUP=(FATFS*)Mem_malloc(INSRAM,sizeof(FATFS));	

  f_mount(fsUP,"2:",1); 	//����U��
	BRUSH_COLOR=RED;   

 	while(font_init()) 				//����ֿ�
	{	    
		LCD_DisplayString(60,50,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill_onecolor(60,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}
  LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(10,40,16,"Author:Clever");			    	 
	LCD_DisplayHZstr(30,80,24,"21 USB U��ʵ��");					    	 
	LCD_DisplayHZstr(30,110,16,"2015��3��26��");	    	 
	LCD_DisplayHZstr(30,140,16,"�豸������...");			 		
	//��ʼ��USB����
 	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks);  
	while(1)
	{
		USBH_Process(&USB_OTG_Core, &USB_Host);
		delay_ms(1);
		t++;
		if(t==200)
		{
			LED0=!LED0;
			t=0;
		}
	}	
}










