#ifndef __USART4_H
#define __USART4_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART4_REC_NUM  			100  	//定义最大接收字节数 200
extern u8 uart_byte_count;          //uart_byte_count要小于USART_REC_LEN
extern u8 receive_str[USART4_REC_NUM];  

void uart4_init(u32 bound);
void uart4SendChars(u8 *str, u16 strlen);

extern double Xe,Ye,ThetaE;

#endif


