#ifndef __CAN2_H
#define __CAN2_H	 
#include "common.h"	 

//////////////////////////////////////////////////////////////////////////////////	 


	
//CAN2����RX0�ж�ʹ��
#define CAN2_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
										 							 				    
u8 CAN2_Mode_Init(u8 mode);//CAN��ʼ��
 
u8 CAN2_Send_Msg(u16 id,u8* msg,u8 len);					//��������

u8 CAN2_Receive_Msg(u8 *buf);							//��������
#endif

















