#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART1_REC_NUM  			128  	//�����������ֽ��� 128
extern u8 byte_count_232;          //uart_byte_countҪС��USART_REC_LEN
extern u8 receive_str_232[USART1_REC_NUM];  
extern u8 send_str_232[USART1_REC_NUM];

void uart1_init(u32 bound);
void uart1SendChars(u8 *str, u16 strlen);

#endif


