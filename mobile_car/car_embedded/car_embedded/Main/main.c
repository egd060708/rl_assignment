#include "led.h"
#include "can1.h"
#include "can2.h"
#include "beep.h"
#include "timer.h"
#include "interface.h"
#include "pstwo.h"
#include "usart1.h"
/*********************************************************************************
*********************�������� STM32F407Ӧ�ÿ�����(���ݰ�)*************************
**********************************************************************************
* �ļ�����: ����13 CANͨ��ʵ��                                                   *
* �ļ�������canͨ��                                                              *
* �������ڣ�2018.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ����                                                                     *
* �Ա����̣�https://shop125046348.taobao.com                                     *
* ��    ���������̴��������ѧϰ�ο�                                             *
**********************************************************************************
*********************************************************************************/

//??????,??printf??,??????use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//??????????                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//??_sys_exit()??????????    
void _sys_exit(int x) 
{ 
	x = x; 
} 

#endif 


extern u16 Handkey;
int Stop,ref;//extern int Stop,ref;Stop = rtb_Stop;ref = rtb_Angle_ref;
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;
int main(void)
{ 
	
	u8 CAN1_mode=0; //CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	u8 CAN2_mode=0; //CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//����ϵͳ�ж����ȼ�����2
	delay_init();    //��ʼ����ʱ����
	uart1_init(9600);	    //���ڳ�ʼ��������Ϊ9600 �������ʼ��������Ϊ921600
	LED_Init();			 //��ʼ��LED
	TIM2_Init(5000-1,8400-1); //��ʼ����ʱ��
	BEEP_Init();     //��ʼ��������
	
	PS2_Init();
	PS2_SetInit();
	delay_ms(500);
	CAN1_Mode_Init(CAN1_mode);//CAN��ʼ����ͨģʽ,������500Kbps   ����canͨ��
	CAN2_Mode_Init(CAN2_mode);//CAN��ʼ����ͨģʽ,������500Kbps 
  //������Ϊ:42M/((1+6+7)*6)=500Kbps	
 	


	 /*��printf()֮��ĺ�����ʹ���˰�����ģʽ��ʹ�ñ�׼��ᵼ�³����޷�
          ����,�����ǽ������:ʹ��΢��,��Ϊʹ��΢��Ļ�,����ʹ�ð�����ģʽ. 
          ���ڹ������Եġ�Target��-����Code Generation���й�ѡ��Use MicroLIB����
          ���Ժ�Ϳ���ʹ��printf��sprintf������*/


	printf("���ڴ�ӡ����!!!!!\r\n");
	BEEP_Times(2);
	
while(1)
	{	
		
		PS2_Receive ();
		MainFCN();
		printf("     Handkey:%d",Handkey);
		printf("     Stop:%d",Stop);
		printf("     ref:%d",ref);
		printf("\n");
		delay_ms(70);
		if(Stop){
		LED0=!LED0;}//��ʾϵͳ��������	  
	} 
}

