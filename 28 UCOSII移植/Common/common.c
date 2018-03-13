#include "common.h"
#include "includes.h"				//ucos ʹ��	    

/*********************************************************************************
*************************MCU���� STM32F407���Ŀ�����******************************
**********************************************************************************
* �ļ�����: common.c                                                             *
* �ļ���������������������õĹ����ļ�                                           *
* �������ڣ�2017.09.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ���������������Ͷ��塢IO��λ���塢λ�ζ�������ʱ��������                 * 
**********************************************************************************
*********************************************************************************/	  

/****************************************************************************
* ��    ��: void GPIO_group_OUT(_gpio_group *group,u16 outdata)
* ��    �ܣ�ʹ������16��IO�����һ��16λ���������
* ��ڲ�����*group�� ����16��IO��ΪԪ�صĽṹ��ָ��
            outdata: 16λ�����ֵ
* ���ز�������
* ˵    ����outdata�Ӹ�λ��ʼ��ֵ
****************************************************************************/
void GPIO_group_OUT(_gpio_group *group,u16 outdata)
{
  u8 t;
	for(t=0;t<16;t++)
    {               
        if((outdata&0x8000)>>15)  
				{
						switch(t)
						{
								case 0:	   group->data15=1; break;
								case 1:	   group->data14=1; break;
								case 2:	   group->data13=1; break;
								case 3:	   group->data12=1; break;
								case 4:	   group->data11=1; break;
								case 5:	   group->data10=1; break;
								case 6:	   group->data9=1;  break;
								case 7:	   group->data8=1;  break;
								case 8:	   group->data7=1;  break;
								case 9:	   group->data6=1;  break;
								case 10:	 group->data5=1;  break;
								case 11:	 group->data4=1;  break;
								case 12:	 group->data3=1;  break;
								case 13:	 group->data2=1;  break;
								case 14:	 group->data1=1;  break;
								case 15:	 group->data0=1;  break;
						}
				}
				else
				{
				  switch(t)
						{
								case 0:	   group->data15=0; break;
								case 1:	   group->data14=0; break;
								case 2:	   group->data13=0; break;
								case 3:	   group->data12=0; break;
								case 4:	   group->data11=0; break;
								case 5:	   group->data10=0; break;
								case 6:	   group->data9=0;  break;
								case 7:	   group->data8=0;  break;
								case 8:	   group->data7=0;  break;
								case 9:	   group->data6=0;  break;
								case 10:	 group->data5=0;  break;
								case 11:	 group->data4=0;  break;
								case 12:	 group->data3=0;  break;
								case 13:	 group->data2=0;  break;
								case 14:	 group->data1=0;  break;
								case 15:	 group->data0=0;  break;
						}
				}
     outdata<<=1; 	
	  }
}
/****************************************************************************
* ��    ��: void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
* ��    �ܣ�λ�β���ʵ�֣�ͬһIO�ڵļ�λ�����������
* ��ڲ�����* GPIOx��  ��Ӧ��IO��
*           start_bit: �����������ʼλ
*           bit_size:  Ҫ���������λ��
* ���ز�������
* ˵    ����start_bit: 0~14
            bit_size:  1~16 
            bit_size<=16-start_bit
****************************************************************************/
void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
{
  u8 i=0;
	u16 bu1=0;u16 middata=1;

	if( bit_size>(16-start_bit) ) 
     bit_size=16-start_bit;
	
	i=start_bit;
	if(i>0)
		 {
			 while(i--)
         { bu1+=middata; middata*=2;}
		 }
	
   assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
   
	 GPIOx->ODR&=(  ( (0xffff<<bit_size) <<start_bit ) |bu1   ); 
	 GPIOx->ODR|=(outdata<<start_bit);		 
}

/*****************************************************************************
*****************************���´���ο�����*********************************
*****************************************************************************/
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

//��ǰ�治ͬ���ǣ�ǰ��δ�ʱ�������ڲ�ѯ�Ĵ���ģʽ
//��ʹ��UCOSʱ����Ҫ�õδ�ʱ���ṩ���Ĳ��Ҳ�������
//��ʱ�жϣ����Դ�ʱ�ĵδ�ʱ���������ж�ģʽ 

static u8  fac_us=0; //us��ʱ������			   

/****************************************************************************
* ��    ��: delay_init()
* ��    �ܣ���ʱ������ʼ��
* ��ڲ�������
* ���ز�������
* ˵    ����ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
****************************************************************************/			   
void delay_init(void)
{
	u32 retool;

 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8	    
	retool=SYSCLK/8;		//ÿ���ӵļ�������   
	
	retool*=1000000/OS_TICKS_PER_SEC;//����OS_TICKS_PER_SEC�趨���ʱ��
							                     //reloadΪ24λ�Ĵ���,���ֵ:16777216,��168M��,Լ��0.7989s����	  
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж� ���ж� �жϣ�
	SysTick->LOAD=retool; 	//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK
}								    

/****************************************************************************
* ��    ��: void delay_us(u32 nus)
* ��    �ܣ���ʱnus
* ��ڲ�����Ҫ��ʱ��΢����
* ���ز�������
* ˵    ����ucos�ṩ����С��ʱΪms����ʵ�������кܶ�ʱ���õ�us����ͨ������ʵ��.
*           �����ڽ���us��ʱ�ǹر�ucos������ȣ���ʱ���ڿ����������
****************************************************************************/	    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 initial,operation,count=0;
	u32 reload=SysTick->LOAD;	//LOAD��ֵ
	
	ticks=nus*fac_us; 			  //��Ҫ�Ľ�����	  		 
	count=0;
	OSSchedLock();				//�ر�ucos������ȣ���ֹ���us��ʱ
	initial=SysTick->VAL;    //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		operation=SysTick->VAL;	
		if(operation!=initial)
		{	    
			if(operation<initial)count+=initial-operation;//SYSTICK��һ���ݼ��ļ����� 
			else count+=reload-operation+initial;	    
			initial=operation;
			if(count>=ticks)break; //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	};
	OSSchedUnlock();			//����ucos���� 									    
}

//ms��ʱ��ucos�ṩ�� OSTimeDlyHMSM(......);

//systick�жϷ�����
void SysTick_Handler(void)
{				   
	OSIntEnter();		   //�����ж�
  OSTimeTick();      //����ucos��ʱ�ӷ������               
  OSIntExit();       //���������л����ж�
}


			 
 
