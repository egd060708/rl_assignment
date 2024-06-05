/*TTL*/

#include "usart4.h"
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h" 

/*********************************************************************************
***********************�������� STM32F407������(���ݰ�)***************************
**********************************************************************************
* �ļ�����: usart4.c                                                             *
* �ļ�������USART4ʹ��                                                           *
* �������ڣ�2018.03.06                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ������־���USART1����LED��������������                    * 
**********************************************************************************
*********************************************************************************/	

u8 receive_str[USART4_REC_NUM];     //���ջ�������,���USART_REC_LEN���ֽ� 
u8 uart_byte_count=0;

char YeStr[5],XeStr[5],ThetaEStr[5];
double Xe,Ye,ThetaE;

/****************************************************************************
* ��    ��: void uart3_init(u32 bound)
* ��    �ܣ�USART1��ʼ��
* ��ڲ�����bound��������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart4_init(u32 bound)
{   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART4ʱ�� 
	 	USART_DeInit(UART4);  //��λ����4
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);  //GPIOA0����ΪUSART4
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); //GPIOA1����ΪUSART4
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOA0��GPIOA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);          //��ʼ��
   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(UART4, &USART_InitStructure); //��ʼ������1	
  USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���4 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);         //��������ж�
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;      //����4�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		   //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	  //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

//����1����һ���ַ�
void uart4SendChar(u8 ch)
{      
	while((UART4->SR&0x40)==0);  
    UART4->DR = (u8) ch;      
}
/****************************************************************************
* ��    ��: void uart1SendChars(u8 *str, u16 strlen)
* ��    �ܣ�����1����һ�ַ���
* ��ڲ�����*str�����͵��ַ���
            strlen���ַ�������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart4SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { uart4SendChar(*(str + k)); k++; }   //ѭ������,ֱ���������   
    while (k < strlen); 
} 

//����4�жϷ������
void UART4_IRQHandler(void)  
{
	u8 rec_data;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж� 
		{
				rec_data =(u8)USART_ReceiveData(UART4);         //(USART1->DR) ��ȡ���յ�������
        if(rec_data=='S')		  	                         //�����S����ʾ��������Ϣ����ʼλ   ����������д
				{
					uart_byte_count=0x01; 
				}

			else if(rec_data=='E')		                         //���E����ʾ��������Ϣ���͵Ľ���λ
				{
//					if(strcmp("Light_led1",(char *)receive_str)==0)        LED1=0;	//����LED1
//					else if(strcmp("Close_led1",(char *)receive_str)==0)   LED1=1;	//����LED1
//					else if(strcmp("Open_beep",(char *)receive_str)==0)    BEEP=1; 	//��������
//					else if(strcmp("Close_beep",(char *)receive_str)==0)   BEEP=0; 	//����������
					
					strncpy(YeStr,(char *)receive_str,4);
					strncpy(XeStr,(char *)receive_str+8,4);
					strncpy(ThetaEStr,(char *)receive_str+12,4);
					
					XeStr[4] = '\0';
					YeStr[4] = '\0';
					ThetaEStr[4] = '\0';
					
					double num1 = atof(XeStr);
					double num2 = atof(YeStr);
					double num3 = atof(ThetaEStr);
					
					Xe = (double)(num1)-5000;
					Ye = (double)(num2)-5000;
					ThetaE = -(double)(num3)+5000;

//					printf("Xe: %.2f\n", Xe);
//					printf("Ye: %.2f\n", Ye);
//					printf("ThetaE: %.2f\n", ThetaE);

					for(uart_byte_count=0;uart_byte_count<32;uart_byte_count++)receive_str[uart_byte_count]=0x00;
					uart_byte_count=0;    
				}				  
			else if((uart_byte_count>0)&&(uart_byte_count<=USART4_REC_NUM))
				{
				   receive_str[uart_byte_count-1]=rec_data;
				   uart_byte_count++;
				}                		 
   } 
} 

