#ifndef __DS18B20_H
#define __DS18B20_H 
#include "common.h"   

//////////////////////////////////////////////////////////////////////////////////	 

//IO��������
#define DS18B20_IO_IN()  {GPIOA->MODER&=0XCFFFFFFF;GPIOA->MODER|=0;}	//PA15����ģʽ
#define DS18B20_IO_OUT() {GPIOA->MODER&=0XCFFFFFFF;GPIOA->MODER|=0x40000000;} 	//PA15���ģʽ
 
////IO��������											   
#define	DS18B20_DQ_OUT PAout(15) //���ݶ˿�	PA15
#define	DS18B20_DQ_IN  PAin(15)  //���ݶ˿�	PA15
   	
u8 DS18B20_Init(void);			   //��ʼ��DS18B20
short DS18B20_Get_Temp(void);	 //��ȡ�¶�
void DS18B20_Start(void);		   //��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		  //����һ���ֽ�
u8 DS18B20_Read_Bit(void);	  	//����һ��λ
u8 DS18B20_Check(void);			    //����Ƿ����DS18B20
void DS18B20_Rst(void);			    //��λDS18B20    
#endif















