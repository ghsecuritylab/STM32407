#ifndef __RS485_H
#define __RS485_H			 
#include "common.h"	 								  

	  	
extern u8 receive_str_485[128]; 	//���ջ���,���512���ֽ�
extern u8 send_str_485[128]; 	//���ջ���,���512���ֽ�
extern u8 byte_count_485;   			  //���յ������ݳ���

//ģʽ����
#define RS485_TX_EN		PGout(6)	    //485ģʽ����.0,����;1,����.

														 
void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
 
#endif	   
















