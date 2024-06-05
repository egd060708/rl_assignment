#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART1_REC_NUM  			100  	//�����������ֽ��� 200
extern u8 uart1_byte_count;          //uart1_byte_countҪС��USART_REC_LEN
extern u8 receive_uart1_str[USART1_REC_NUM];  

void uart1_init(u32 bound);
void uart1SendChars(u8 *str, u16 strlen);


#endif


