#include "led.h"
#include "can1.h"
#include "can2.h"
#include "beep.h"
#include "timer.h"
#include "interface.h"
#include "pstwo.h"
#include "usart1.h"
/*********************************************************************************
*********************启明欣欣 STM32F407应用开发板(轻奢版)*************************
**********************************************************************************
* 文件名称: 例程13 CAN通信实验                                                   *
* 文件简述：can通信                                                              *
* 创建日期：2018.08.30                                                           *
* 版    本：V1.0                                                                 *
* 作    者：Clever                                                               *
* 说    明：                                                                     *
* 淘宝店铺：https://shop125046348.taobao.com                                     *
* 声    明：本例程代码仅用于学习参考                                             *
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
	
	u8 CAN1_mode=0; //CAN工作模式;0,普通模式;1,环回模式
	u8 CAN2_mode=0; //CAN工作模式;0,普通模式;1,环回模式
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//设置系统中断优先级分组2
	delay_init();    //初始化延时函数
	uart1_init(9600);	    //串口初始化波特率为9600 ，建议初始化波特率为921600
	LED_Init();			 //初始化LED
	TIM2_Init(5000-1,8400-1); //初始化定时器
	BEEP_Init();     //初始化蜂鸣器
	
	PS2_Init();
	PS2_SetInit();
	delay_ms(500);
	CAN1_Mode_Init(CAN1_mode);//CAN初始化普通模式,波特率500Kbps   两个can通信
	CAN2_Mode_Init(CAN2_mode);//CAN初始化普通模式,波特率500Kbps 
  //则波特率为:42M/((1+6+7)*6)=500Kbps	
 	


	 /*因printf()之类的函数，使用了半主机模式。使用标准库会导致程序无法
          运行,以下是解决方法:使用微库,因为使用微库的话,不会使用半主机模式. 
          请在工程属性的“Target“-》”Code Generation“中勾选”Use MicroLIB“这
          样以后就可以使用printf，sprintf函数了*/


	printf("串口打印测试!!!!!\r\n");
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
		LED0=!LED0;}//提示系统正在运行	  
	} 
}

